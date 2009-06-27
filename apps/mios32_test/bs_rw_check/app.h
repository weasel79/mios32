/*
 * Header file of application
 *
 * ==========================================================================
 *
 *  Copyright (C) <year> <your name> (<your email address>)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#ifndef _APP_H
#define _APP_H


/////////////////////////////////////////////////////////////////////////////
// Global definitions
/////////////////////////////////////////////////////////////////////////////

// define the number of banksticks you want to check (1 - 8)
#define BS_CHECK_NUM_BS 1

// define the number of 64-byte blocks per bankstick
// 24LC512: 1014
// 24LC256: 512
#define BS_CHECK_NUM_BLOCKS_PER_BS 1024

// define the number of test-runs you want the application to go through.
// can be used to test IIC stability.
#define BS_CHECK_NUM_RUNS 3

/////////////////////////////////////////////////////////////////////////////
// Global Types
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

extern void APP_Init(void);
extern void APP_Background(void);
extern void APP_NotifyReceivedEvent(mios32_midi_port_t port, mios32_midi_package_t midi_package);
extern void APP_NotifyReceivedSysEx(mios32_midi_port_t port, u8 sysex_byte);
extern void APP_NotifyReceivedCOM(mios32_com_port_t port, u8 byte);
extern void APP_SRIO_ServicePrepare(void);
extern void APP_SRIO_ServiceFinish(void);
extern void APP_DIN_NotifyToggle(u32 pin, u32 pin_value);
extern void APP_ENC_NotifyChange(u32 encoder, s32 incrementer);
extern void APP_AIN_NotifyChange(u32 pin, u32 pin_value);


/////////////////////////////////////////////////////////////////////////////
// Export global variables
/////////////////////////////////////////////////////////////////////////////


#endif /* _APP_H */