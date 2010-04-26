/*********************************************************
 * Copyright (C) 2008 VMware, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation version 2.1 and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the Lesser GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA.
 *
 *********************************************************/

/*
 * toolbox-cmd.h --
 *
 *     Common defines used by the toolbox-cmd.
 */
#ifndef _TOOLBOX_CMD_INT_H_
#define _TOOLBOX_CMD_INT_H_

#define VMW_TEXT_DOMAIN "toolboxcmd"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#   include "getoptwin32.h"
#else
#   include <getopt.h>
#   include <sysexits.h>
#   include <unistd.h>
#endif

#include "toolboxInt.h"
#include "vmGuestLib.h"

/*
 * Some platforms (such as Win32) don't have sysexits.h and thus don't have
 * generic program exit codes.
 */

#ifndef EX_USAGE
#define EX_USAGE 64
#endif

#ifndef EX_UNAVAILABLE
#define EX_UNAVAILABLE 69
#endif

#ifndef EX_OSFILE
#define EX_OSFILE 72
#endif

#ifndef EX_TEMPFAIL
#define EX_TEMPFAIL 75
#endif

#ifndef EX_NOPERM
#define EX_NOPERM 77
#endif

/*
 * We want to have commands and arguments on Windows to be
 * case-instensitive, everywhere else we expect lowercase
 * for commands and case-sensitivity for arguments.
 */
#ifdef _WIN32
#   define toolbox_strcmp  stricmp
#else
#   define toolbox_strcmp  strcmp
#endif

/*
 * Common functions.
 */

void
ToolsCmd_MissingEntityError(const char *name,
                            const char *entity);

void
ToolsCmd_UnknownEntityError(const char *name,
                            const char *entity,
                            const char *str);


/**
 * A shorthand macro for declaring a command entry. This just declares
 * two functions ("foo_Command" and "foo_Help" for a command "foo").
 * The command implementation should provide those functions, which will
 * be used by the main dispatch table when executing commands.
 */

#define DECLARE_COMMAND(name)             \
   int name##_Command(char **argv,        \
                      int argc,           \
                      gboolean quiet);    \
   void name##_Help(const char *progName, \
                    const char *cmd);

DECLARE_COMMAND(Device);
DECLARE_COMMAND(Disk);
DECLARE_COMMAND(Script);
DECLARE_COMMAND(Stat);
DECLARE_COMMAND(TimeSync);

#endif /*_TOOLBOX_CMD_H_*/
