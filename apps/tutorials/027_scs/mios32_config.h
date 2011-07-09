// $Id$
/*
 * Local MIOS32 configuration file
 *
 * this file allows to disable (or re-configure) default functions of MIOS32
 * available switches are listed in $MIOS32_PATH/modules/mios32/MIOS32_CONFIG.txt
 *
 */

#ifndef _MIOS32_CONFIG_H
#define _MIOS32_CONFIG_H

// The boot message which is print during startup and returned on a SysEx query
#define MIOS32_LCD_BOOT_MSG_LINE1 "Tutorial #027"
#define MIOS32_LCD_BOOT_MSG_LINE2 "(C) 2011 T.Klose"


// the used encoder type (see mios32_enc.h)
#define SCS_ENC_TYPE DETENTED1

#endif /* _MIOS32_CONFIG_H */
