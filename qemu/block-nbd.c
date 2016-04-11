/*
 * QEMU Block driver for  NBD
 *
 * Copyright (C) 2008 Bull S.A.S.
 *     Author: Laurent Vivier <Laurent.Vivier@bull.net>
 *
 * Some parts:
 *    Copyright (C) 2007 Anthony Liguori <anthony@codemonkey.ws>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * WinQEMU GPL Disclaimer: For the avoidance of doubt, except that if any license choice
 * other than GPL is available it will apply instead, WinQEMU elects to use only the 
 * General Public License version 3 (GPLv3) at this time for any software where a choice of 
 * GPL license versions is made available with the language indicating that GPLv3 or any later
 * version may be used, or where a choice of which version of the GPL is applied is otherwise unspecified.
 * 
 * Please contact Yan Wen (celestialwy@gmail.com) if you need additional information or have any questions.
 */
 
#include "qemu-common.h"
#include "nbd.h"

#include <sys/types.h>
#include <unistd.h>

typedef struct BDRVNBDState {
    int sock;
    off_t size;
    size_t blocksize;
} BDRVNBDState;

static int nbd_open(BlockDriverState *bs, const char* filename, int flags)
{
    BDRVNBDState *s = bs->opaque;
    const char *host;
    const char *unixpath;
    int sock;
    off_t size;
    size_t blocksize;
    int ret;

    if ((flags & BDRV_O_CREAT))
        return -EINVAL;

    if (!strstart(filename, "nbd:", &host))
        return -EINVAL;

    if (strstart(host, "unix:", &unixpath)) {

        if (unixpath[0] != '/')
            return -EINVAL;

        sock = unix_socket_outgoing(unixpath);

    } else {
        uint16_t port;
        char *p, *r;
        char hostname[128];

        pstrcpy(hostname, 128, host);

        p = strchr(hostname, ':');
        if (p == NULL)
            return -EINVAL;

        *p = '\0';
        p++;

        port = strtol(p, &r, 0);
        if (r == p)
            return -EINVAL;
        sock = tcp_socket_outgoing(hostname, port);
    }

    if (sock == -1)
        return -errno;

    ret = nbd_receive_negotiate(sock, &size, &blocksize);
    if (ret == -1)
        return -errno;

    s->sock = sock;
    s->size = size;
    s->blocksize = blocksize;

    return 0;
}

static int nbd_read(BlockDriverState *bs, int64_t sector_num,
                    uint8_t *buf, int nb_sectors)
{
    BDRVNBDState *s = bs->opaque;
    struct nbd_request request;
    struct nbd_reply reply;

    request.type = NBD_CMD_READ;
    request.handle = (uint64_t)(intptr_t)bs;
    request.from = sector_num * 512;;
    request.len = nb_sectors * 512;

    if (nbd_send_request(s->sock, &request) == -1)
        return -errno;

    if (nbd_receive_reply(s->sock, &reply) == -1)
        return -errno;

    if (reply.error !=0)
        return -reply.error;

    if (reply.handle != request.handle)
        return -EIO;

    if (nbd_wr_sync(s->sock, buf, request.len, 1) != request.len)
        return -EIO;

    return 0;
}

static int nbd_write(BlockDriverState *bs, int64_t sector_num,
                     const uint8_t *buf, int nb_sectors)
{
    BDRVNBDState *s = bs->opaque;
    struct nbd_request request;
    struct nbd_reply reply;

    request.type = NBD_CMD_WRITE;
    request.handle = (uint64_t)(intptr_t)bs;
    request.from = sector_num * 512;;
    request.len = nb_sectors * 512;

    if (nbd_send_request(s->sock, &request) == -1)
        return -errno;

    if (nbd_wr_sync(s->sock, (uint8_t*)buf, request.len, 0) != request.len)
        return -EIO;

    if (nbd_receive_reply(s->sock, &reply) == -1)
        return -errno;

    if (reply.error !=0)
        return -reply.error;

    if (reply.handle != request.handle)
        return -EIO;

    return 0;
}

static void nbd_close(BlockDriverState *bs)
{
    BDRVNBDState *s = bs->opaque;
    struct nbd_request request;

    request.type = NBD_CMD_DISC;
    request.handle = (uint64_t)(intptr_t)bs;
    request.from = 0;
    request.len = 0;
    nbd_send_request(s->sock, &request);

    close(s->sock);
}

static int64_t nbd_getlength(BlockDriverState *bs)
{
    BDRVNBDState *s = bs->opaque;

    return s->size;
}

#ifndef _MSC_VER
BlockDriver bdrv_nbd = {
    "nbd",
    sizeof(BDRVNBDState),
    NULL, /* no probe for protocols */
    nbd_open,
    nbd_read,
    nbd_write,
    nbd_close,
    .bdrv_getlength = nbd_getlength,
    .protocol_name = "nbd",
};
#else
BlockDriver bdrv_nbd = {
	"nbd",					//const char *format_name;
	sizeof(BDRVNBDState),	//int instance_size;
	NULL,					//int (*bdrv_probe)(const uint8_t *buf, int buf_size, const char *filename);
	nbd_open,				//int (*bdrv_open)(BlockDriverState *bs, const char *filename, int flags);
	nbd_read,				//int (*bdrv_read)(BlockDriverState *bs, int64_t sector_num, uint8_t *buf, int nb_sectors);
	nbd_write,				//int (*bdrv_write)(BlockDriverState *bs, int64_t sector_num,	const uint8_t *buf, int nb_sectors);
	nbd_close,				//void (*bdrv_close)(BlockDriverState *bs);
	NULL,					//int (*bdrv_create)(const char *filename, int64_t total_sectors, const char *backing_file, int flags);
	NULL,					//void (*bdrv_flush)(BlockDriverState *bs);
	NULL,					//int (*bdrv_is_allocated)(BlockDriverState *bs, int64_t sector_num, int nb_sectors, int *pnum);
	NULL,					//int (*bdrv_set_key)(BlockDriverState *bs, const char *key);
	NULL,					//int (*bdrv_make_empty)(BlockDriverState *bs);

	/* aio */
	NULL,					//BlockDriverAIOCB *(*bdrv_aio_read)(BlockDriverState *bs, int64_t sector_num, uint8_t *buf, int nb_sectors, BlockDriverCompletionFunc *cb, void *opaque);
	NULL,					//BlockDriverAIOCB *(*bdrv_aio_write)(BlockDriverState *bs, int64_t sector_num, const uint8_t *buf, int nb_sectors, BlockDriverCompletionFunc *cb, void *opaque);
	NULL,					//void (*bdrv_aio_cancel)(BlockDriverAIOCB *acb);
	0,						//int aiocb_size;

	"nbd",					//const char *protocol_name;
	NULL,					//int (*bdrv_pread)(BlockDriverState *bs, int64_t offset, uint8_t *buf, int count);
	NULL,					//int (*bdrv_pwrite)(BlockDriverState *bs, int64_t offset, const uint8_t *buf, int count);
	NULL,					//int (*bdrv_truncate)(BlockDriverState *bs, int64_t offset);
	bdrv_getlength,			//int64_t (*bdrv_getlength)(BlockDriverState *bs);
	NULL,					//int (*bdrv_write_compressed)(BlockDriverState *bs, int64_t sector_num, const uint8_t *buf, int nb_sectors);

	NULL,					//int (*bdrv_snapshot_create)(BlockDriverState *bs, QEMUSnapshotInfo *sn_info);
	NULL,					//int (*bdrv_snapshot_goto)(BlockDriverState *bs, const char *snapshot_id);
	NULL,					//int (*bdrv_snapshot_delete)(BlockDriverState *bs, const char *snapshot_id);
	NULL,					//int (*bdrv_snapshot_list)(BlockDriverState *bs, QEMUSnapshotInfo **psn_info);
	NULL,					//int (*bdrv_get_info)(BlockDriverState *bs, BlockDriverInfo *bdi);

	/* removable device specific */
	NULL,					//int (*bdrv_is_inserted)(BlockDriverState *bs);
	NULL,					//int (*bdrv_media_changed)(BlockDriverState *bs);
	NULL,					//int (*bdrv_eject)(BlockDriverState *bs, int eject_flag);
	NULL,					//int (*bdrv_set_locked)(BlockDriverState *bs, int locked);

	/* to control generic scsi devices */
	NULL,					//int (*bdrv_ioctl)(BlockDriverState *bs, unsigned long int req, void *buf);

	NULL,					//BlockDriverAIOCB *free_aiocb;
	NULL					//struct BlockDriver *next;
};


#endif