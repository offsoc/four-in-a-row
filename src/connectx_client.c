/* connectx_client.c
 *
 * Four-in-a-row for GNOME
 * Copyright (C) 2006 -  Andreas Røsdal <andrearo@pvv.ntnu.no>
 *
 * This game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 * USA
 */


/* Generated by GGZComm/ruby version 0.4 */
/* Protocol 'connectx', version '2' */

#include "connectx_client.h"
#include <stdlib.h>
#include <ggz.h>
//#define GGZCOMM_DEBUG 0
#include <stdio.h>

#define ggz__seat_open 1

static notifier_func_type notifier_func = NULL;
static error_func_type error_func = NULL;
static int fd = -1;
static int ret;
static int requirelink = 0;
static int nextlink;

static void ggzcomm_error (void);

void
ggzcomm_sndoptions (void)
{
  ret = ggz_write_int (fd, sndoptions);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_write_char (fd, variables.boardheight2);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_write_char (fd, variables.boardwidth2);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_write_char (fd, variables.connectlength2);
  if (ret < 0)
    ggzcomm_error ();
}

void
ggzcomm_sndmove (void)
{
  ret = ggz_write_int (fd, sndmove);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_write_int (fd, variables.column3);
  if (ret < 0)
    ggzcomm_error ();

  requirelink = 1;
  nextlink = rspmove;
}

void
ggzcomm_reqsync (void)
{
  ret = ggz_write_int (fd, reqsync);
  if (ret < 0)
    ggzcomm_error ();

  requirelink = 1;
  nextlink = sndsync;
}

static void
ggzcomm_msgseat (void)
{
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) reading message 'msgseat'...\n");
#endif

  ret = ggz_read_int (fd, &variables.num);
  if (ret < 0)
    ggzcomm_error ();
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) - message was read, 1 parts\n");
#endif

  if (notifier_func)
    (notifier_func) (msgseat);
}

static void
ggzcomm_msgplayers (void)
{
  int i1;

#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) reading message 'msgplayers'...\n");
#endif

  for (i1 = 0; i1 < 2; i1++) {
    ret = ggz_read_int (fd, &variables.seat[i1]);
    if (ret < 0)
      ggzcomm_error ();
    if ((variables.seat[i1] != ggz__seat_open)) {
      ret = ggz_read_string_alloc (fd, &variables.name[i1]);
      if (ret < 0)
	ggzcomm_error ();
    }
  }
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) - message was read, 2 parts\n");
#endif

  if (notifier_func)
    (notifier_func) (msgplayers);
}

static void
ggzcomm_reqmove (void)
{
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) reading message 'reqmove'...\n");
#endif

#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) - message was read, 0 parts\n");
#endif

  if (notifier_func)
    (notifier_func) (reqmove);
}

static void
ggzcomm_rspmove (void)
{
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) reading message 'rspmove'...\n");
#endif

  ret = ggz_read_char (fd, &variables.status);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_read_int (fd, &variables.column);
  if (ret < 0)
    ggzcomm_error ();
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) - message was read, 2 parts\n");
#endif

  if (notifier_func)
    (notifier_func) (rspmove);
}

static void
ggzcomm_msgmove (void)
{
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) reading message 'msgmove'...\n");
#endif

  ret = ggz_read_int (fd, &variables.column2);
  if (ret < 0)
    ggzcomm_error ();
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) - message was read, 1 parts\n");
#endif

  if (notifier_func)
    (notifier_func) (msgmove);
}

static void
ggzcomm_sndsync (void)
{
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) reading message 'sndsync'...\n");
#endif

  ret = ggz_read_char (fd, &variables.boardheight3);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_read_char (fd, &variables.boardwidth3);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_read_char (fd, &variables.connectlength3);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_read_char (fd, &variables.turn);
  if (ret < 0)
    ggzcomm_error ();
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) - message was read, 4 parts\n");
#endif

  if (notifier_func)
    (notifier_func) (sndsync);
}

static void
ggzcomm_msggameover (void)
{
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) reading message 'msggameover'...\n");
#endif

  ret = ggz_read_char (fd, &variables.winner);
  if (ret < 0)
    ggzcomm_error ();
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) - message was read, 1 parts\n");
#endif

  if (notifier_func)
    (notifier_func) (msggameover);
}

static void
ggzcomm_reqoptions (void)
{
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) reading message 'reqoptions'...\n");
#endif

  ret = ggz_read_char (fd, &variables.minboardwidth);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_read_char (fd, &variables.maxboardwidth);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_read_char (fd, &variables.minboardheight);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_read_char (fd, &variables.maxboardheight);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_read_char (fd, &variables.minconnectlength);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_read_char (fd, &variables.maxconnectlength);
  if (ret < 0)
    ggzcomm_error ();
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) - message was read, 6 parts\n");
#endif

  if (notifier_func)
    (notifier_func) (reqoptions);
}

static void
ggzcomm_msgoptions (void)
{
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) reading message 'msgoptions'...\n");
#endif

  ret = ggz_read_char (fd, &variables.boardwidth);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_read_char (fd, &variables.boardheight);
  if (ret < 0)
    ggzcomm_error ();
  ret = ggz_read_char (fd, &variables.connectlength);
  if (ret < 0)
    ggzcomm_error ();
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) - message was read, 3 parts\n");
#endif

  if (notifier_func)
    (notifier_func) (msgoptions);
}

void
ggzcomm_network_main (void)
{
  int opcode;

#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) reading opcode...\n");
#endif

  ggz_read_int (fd, &opcode);

#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) -> opcode is %i\n", opcode);
#endif

  if (requirelink) {
    if (opcode != nextlink)
      ggzcomm_error ();
    requirelink = 0;
  }

  switch (opcode) {
  case msgseat:
    ggzcomm_msgseat ();
    break;
  case msgplayers:
    ggzcomm_msgplayers ();
    break;
  case reqmove:
    ggzcomm_reqmove ();
    break;
  case rspmove:
    ggzcomm_rspmove ();
    break;
  case msgmove:
    ggzcomm_msgmove ();
    break;
  case sndsync:
    ggzcomm_sndsync ();
    break;
  case msggameover:
    ggzcomm_msggameover ();
    break;
  case reqoptions:
    ggzcomm_reqoptions ();
    break;
  case msgoptions:
    ggzcomm_msgoptions ();
    break;
  }
}

void
ggzcomm_set_notifier_callback (notifier_func_type f)
{
  notifier_func = f;
}

void
ggzcomm_set_error_callback (error_func_type f)
{
  error_func = f;
}

void
ggzcomm_set_fd (int usefd)
{
  fd = usefd;
}

int
ggzcomm_get_fd (void)
{
  return fd;
}

static void
ggzcomm_error (void)
{
#ifdef GGZCOMM_DEBUG
  printf ("(ggzcomm) error!\n");
#endif

  if (error_func)
    (error_func) ();
}