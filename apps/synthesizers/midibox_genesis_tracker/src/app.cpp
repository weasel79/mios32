/*
 * MIDIbox Genesis Tracker: Main application
 *
 * ==========================================================================
 *
 *  Copyright (C) 2016 Sauraen (sauraen@gmail.com)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

/////////////////////////////////////////////////////////////////////////////
// Include files
/////////////////////////////////////////////////////////////////////////////

#include <mios32.h>
#include "app.h"

#include <genesis.h>
#include <file.h>
#include <blm_x.h>

#include "vgmsourcestream.h"
#include "vgmhead.h"
#include "vgmplayer.h"
#include "vgmplayer_ll.h"
#include "frontpanel.h"
#include "interface.h"
#include "genesisstate.h"

u32 DEBUGVAL;
u8 selgvoice;
char* filenamelist;
s32 numfiles;
u8 playbackcommand;
u8 vegasactive;

/////////////////////////////////////////////////////////////////////////////
// This hook is called after startup to initialize the application
// It's delcared as "extern C" so that the MIOS32 programming model can
// access this function - you can safely write your own functions in C++
// In other words: there is no need to add "extern C" to your own functions!
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_Init(void){
    DEBUGVAL = 117;
    // initialize all LEDs
    MIOS32_BOARD_LED_Init(0xffffffff);

    // initialize SD card
    FILE_Init(0);

    //Initialize MBHP_Genesis module
    Genesis_Init();

    //Initialize VGM Player component
    VgmPlayer_Init();
    
    //Initialize Button-LED Matrix driver
    BLM_X_Init();
    
    //Initialize front panel wrapper
    FrontPanel_Init();
    
    //Initialize main interface
    Interface_Init();
    
    /*
    DEBUG_Ring = 0;
    DEBUG_RingState = 0;
    DEBUG_RingDir = 1;
    */
    MIOS32_LCD_Clear();
    MIOS32_LCD_CursorSet(0,0);
    MIOS32_LCD_PrintString("Searching for SD card...");
    
    vegasactive = 0;
    
}


/////////////////////////////////////////////////////////////////////////////
// This task is running endless in background
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_Background(void)
{
    MIOS32_BOARD_LED_Set(0b1000, 0b1000);
    
    if(!vegasactive){
        //Draw Genesis states
        u8 g;
        for(g=0; g<GENESIS_COUNT; g++){
            DrawGenesisActivity(g);
        }
    }
    
    //Play some things on the PSG
    /*
    Genesis_PSGWrite(0, 0b10010000); while(Genesis_CheckPSGBusy(0));
    Genesis_PSGWrite(0, 0b10000000); while(Genesis_CheckPSGBusy(0));
    Genesis_PSGWrite(0, 0b00010000); while(Genesis_CheckPSGBusy(0));
    MIOS32_DELAY_Wait_uS(0xFF00);
    Genesis_PSGWrite(0, 0b10000000); while(Genesis_CheckPSGBusy(0));
    Genesis_PSGWrite(0, 0b00001000); while(Genesis_CheckPSGBusy(0));
    MIOS32_DELAY_Wait_uS(0xFF00);
    Genesis_PSGWrite(0, 0b10000000); while(Genesis_CheckPSGBusy(0));
    Genesis_PSGWrite(0, 0b00000100); while(Genesis_CheckPSGBusy(0));
    MIOS32_DELAY_Wait_uS(0xFF00);
    Genesis_PSGWrite(0, 0b10000000); while(Genesis_CheckPSGBusy(0));
    Genesis_PSGWrite(0, 0b00000010); while(Genesis_CheckPSGBusy(0));
    MIOS32_DELAY_Wait_uS(0xFF00);
    Genesis_PSGWrite(0, 0b10000000); while(Genesis_CheckPSGBusy(0));
    Genesis_PSGWrite(0, 0b00000001); while(Genesis_CheckPSGBusy(0));
    MIOS32_DELAY_Wait_uS(0xFF00);
    */
    //OPN2 piano test patch
    /*
    Genesis_OPN2Write(0, 0, 0x22, 0x00); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0x27, 0x00); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0x2B, 0x00); while(Genesis_CheckOPN2Busy(0));
    for(u8 ah=0; ah<2; ah++){
        Genesis_OPN2Write(0, ah, 0x30, 0x71); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x34, 0x0D); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x38, 0x33); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x3C, 0x01); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x40, 0x23); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x44, 0x2D); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x48, 0x26); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x4C, 0x00); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x50, 0x5F); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x54, 0x99); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x58, 0x5F); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x5C, 0x94); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x60, 0x05); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x64, 0x05); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x68, 0x05); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x6C, 0x07); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x70, 0x02); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x74, 0x02); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x78, 0x02); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x7C, 0x02); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x80, 0x11); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x84, 0x11); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x88, 0x11); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x8C, 0xA6); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x90, 0x00); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x94, 0x00); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x98, 0x00); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0x9C, 0x00); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0xB0, 0x32); while(Genesis_CheckOPN2Busy(0));
        Genesis_OPN2Write(0, ah, 0xB4, 0xC0); while(Genesis_CheckOPN2Busy(0));
    }
    Genesis_OPN2Write(0, 0, 0xA4, 0x22); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0xA0, 0x69); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0x28, 0xF0); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 1, 0xA4, 0x2B); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 1, 0xA0, 0x47); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0x28, 0xF4); while(Genesis_CheckOPN2Busy(0));
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    Genesis_OPN2Write(0, 0, 0x28, 0x00); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0x28, 0x04); while(Genesis_CheckOPN2Busy(0));
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    Genesis_OPN2Write(0, 0, 0xA4, 0x12); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0xA0, 0x69); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0x28, 0xF0); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 1, 0xA4, 0x1B); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 1, 0xA0, 0x47); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0x28, 0xF4); while(Genesis_CheckOPN2Busy(0));
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    Genesis_OPN2Write(0, 0, 0x28, 0x00); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0x28, 0x04); while(Genesis_CheckOPN2Busy(0));
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    Genesis_OPN2Write(0, 0, 0xA4, 0x02); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0xA0, 0x69); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0x28, 0xF0); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 1, 0xA4, 0x0B); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 1, 0xA0, 0x47); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0x28, 0xF4); while(Genesis_CheckOPN2Busy(0));
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    Genesis_OPN2Write(0, 0, 0x28, 0x00); while(Genesis_CheckOPN2Busy(0));
    Genesis_OPN2Write(0, 0, 0x28, 0x04); while(Genesis_CheckOPN2Busy(0));
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    MIOS32_DELAY_Wait_uS(0xFF00);
    */
    //Flash LEDs
    //MIOS32_BOARD_LED_Set(0xF, ((count >> 12) & 0xF));
    MIOS32_BOARD_LED_Set(0b1000, 0b0000);
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called each mS from the main task which also handles DIN, ENC
// and AIN events. You could add more jobs here, but they shouldn't consume
// more than 300 uS to ensure the responsiveness of buttons, encoders, pots.
// Alternatively you could create a dedicated task for application specific
// jobs as explained in $MIOS32_PATH/apps/tutorials/006_rtos_tasks
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_Tick(void){
    static u32 prescaler = 0;
    static u8 sdstate = 0;
    static u8 selfile = 0;
    static VgmSourceStream* vgms = NULL;
    static VgmHead* vgmh = NULL;
    static u8 vegasstate = 0;
    static u32 vegascounter = 0;
    static u8 vegassub = 0;
    static u8 vegastemp1 = 0, vegastemp2 = 0;
    //static u8 row = 0, sr = 0, pin = 0, state = 1;
    //TODO move to its own task
    BLM_X_BtnHandler((void*)&FrontPanel_ButtonChange);
    //TODO testing front panel
    /*
    ++prescaler;
    if(prescaler == 4){
        prescaler = 0;
        row++;
        if(row == 8){
            row = 0;
            pin++;
            if(pin == 8){
                pin = 0;
                sr++;
                if(sr == 11){
                    sr = 0;
                    state++;
                    state &= 1;
                }
            }
        }
    }
    u32 led = (row * 88) + (sr * 8) + pin;
    state = 1;
    BLM_X_LEDSet(led, 0, state);
    */
    /*
    ++prescaler;
    if((prescaler >> 7)){
        prescaler = 0;
        DEBUG_RingState += DEBUG_RingDir;
        DEBUG_RingState &= 0xF;
        FrontPanel_LEDRingSet(DEBUG_Ring, 0, DEBUG_RingState);
    }
    */
    s32 res;
    
    ++prescaler;
    char* tempbuf; u8 i;
    if(prescaler == 500){
        prescaler = 0;
        switch(sdstate){
        case 0:
            res = FILE_CheckSDCard();
            if(res == 3){
                MIOS32_LCD_Clear();
                MIOS32_LCD_CursorSet(0,0);
                MIOS32_LCD_PrintString("Loading list of VGM files...");
                sdstate = 2;
            }else if(res >= 0){
                MIOS32_LCD_Clear();
                MIOS32_LCD_CursorSet(0,0);
                MIOS32_LCD_PrintString("Waiting for SD card to speed up...");
            }else{
                MIOS32_LCD_Clear();
                MIOS32_LCD_CursorSet(0,0);
                MIOS32_LCD_PrintFormattedString("SD Card error %d", res);
                sdstate = 1;
            }
            break;
        case 1:
            //do nothing
            break;
        case 2:
            //Load list of VGM files
            filenamelist = new char[9*MAXNUMFILES];
            numfiles = FILE_GetFiles("/", "vgm", filenamelist, MAXNUMFILES, 0);
            if(numfiles < 0){
                MIOS32_LCD_Clear();
                MIOS32_LCD_CursorSet(0,0);
                MIOS32_LCD_PrintFormattedString("Error %d finding files", numfiles);
                sdstate = 1;
            }else{
                MIOS32_LCD_Clear();
                MIOS32_LCD_CursorSet(0,0);
                MIOS32_LCD_PrintFormattedString("Found %d files", numfiles);
                selfile = 0;
                sdstate = 3;
            }
            break;
        case 3:
            if(playbackcommand != 0){
                switch(playbackcommand){
                case 1:
                    if(selfile < numfiles - 1){
                        ++selfile;
                    }
                    break;
                case 2:
                    if(selfile > 0){
                        --selfile;
                    }
                    break;
                case 3:
                    BLM_X_LEDSet((3 * 88) + (1 * 8) + 4, 0, 1); //Play LED
                    sdstate = 4;
                    break;
                };
                playbackcommand = 0;
            }
            tempbuf = new char[9];
            for(i=0; i<8; i++){
                tempbuf[i] = filenamelist[(9*selfile)+i];
            }
            tempbuf[8] = 0;
            MIOS32_LCD_Clear();
            MIOS32_LCD_CursorSet(0,0);
            MIOS32_LCD_PrintFormattedString("Found %d files", numfiles);
            MIOS32_LCD_CursorSet(0,1);
            MIOS32_LCD_PrintFormattedString("File %d: %s.vgm", selfile, tempbuf);
            delete[] tempbuf;
            break;
        case 4:
            //Load VGM file
            tempbuf = new char[13];
            for(i=0; i<8; i++){
                if(filenamelist[(9*selfile)+i] <= ' ') break;
                tempbuf[i] = filenamelist[(9*selfile)+i];
            }
            tempbuf[i++] = '.';
            tempbuf[i++] = 'v';
            tempbuf[i++] = 'g';
            tempbuf[i++] = 'm';
            tempbuf[i++] = 0;
            vgms = new VgmSourceStream();
            res = vgms->startStream(tempbuf);
            if(res >= 0){
                MIOS32_LCD_Clear();
                MIOS32_LCD_CursorSet(0,0);
                MIOS32_LCD_PrintFormattedString("Loaded VGM!");
                vgms->readHeader();
                vgmh = new VgmHead(vgms);
                vgmh->restart(VgmPlayerLL_GetVGMTime());
                VgmPlayer_AddHead(vgmh);
                sdstate = 5;
            }else{
                MIOS32_LCD_Clear();
                MIOS32_LCD_CursorSet(0,0);
                MIOS32_LCD_PrintFormattedString("Error loading %s", tempbuf);
                delete vgms;
                sdstate = 3;
            }
            delete[] tempbuf;
        case 5:
            if(playbackcommand == 3){
                BLM_X_LEDSet((3 * 88) + (1 * 8) + 4, 0, 0); //Play LED
                VgmPlayer_RemoveHead(vgmh);
                delete vgmh;
                delete vgms;
                Genesis_Reset(0);
                playbackcommand = 0;
                sdstate = 3;
            }
            MIOS32_LCD_Clear();
            MIOS32_LCD_CursorSet(0,0);
            MIOS32_LCD_PrintFormattedString("Playing...");
            break;
        }
    }
    
    /*
    static u32 count = 0;
    static s32 res = 0;
    static u8 gotsdcard = 0;
    
    
    if(count % 10000 == 0){
        if(!gotsdcard){
            res = FILE_CheckSDCard();
            if(res == 3){
                gotsdcard = 1;
                //FILE_PrintSDCardInfos();
            }
        }
        if(gotsdcard){
            if(vgms == NULL){
                vgms = new VgmSourceStream();
                char* filename = new char[50];
                sprintf(filename, "GOODEND.VGM");
                //res = FILE_FileExists(filename);
                //DBG("File existence: %d", res);
                res = vgms->startStream(filename);
                if(res >= 0){
                    DBG("Loaded VGM!");
                    vgms->readHeader();
                    vgmh = new VgmHead(vgms);
                    vgmh->restart(VgmPlayerLL_GetVGMTime());
                    VgmPlayer_AddHead(vgmh);
                }else{
                    DBG("Failed to load VGM");
                }
                delete[] filename;
            }
        }
    }
    */
    
    if(vegasactive){
        switch(vegasstate){
        case 0:
            BLM_X_LEDSet(((vegascounter & 7) * 88) + (vegascounter >> 3), 0, 1);
            if(++vegascounter == 88*8){
                vegascounter = 0;
                vegasstate = 1;
            }
            break;
        case 1:
            BLM_X_LEDSet(((vegascounter & 7) * 88) + (vegascounter >> 3), 0, 0);
            if(++vegascounter == 88*8){
                vegascounter = 0;
                if(++vegassub == 2){
                    vegassub = 0;
                    vegasstate = 2;
                }else{
                    vegasstate = 0;
                }
            }
            break;
        case 2:
            BLM_X_LEDSet(vegascounter, 0, 1);
            if(++vegascounter == 88*8){
                vegascounter = 0;
                vegasstate = 3;
            }
            break;
        case 3:
            BLM_X_LEDSet(vegascounter, 0, 0);
            if(++vegascounter == 88*8){
                vegascounter = 0;
                if(++vegassub == 2){
                    vegassub = 0;
                    vegasstate = 4;
                }else{
                    vegasstate = 2;
                }
            }
            break;
        case 4:
            for(i=0; i<18; i++){
                FrontPanel_LEDRingSet(i, 0, (i&1) ? (15 - ((vegascounter >> 6) & 0xF)) : ((vegascounter >> 6) & 0xF));
            }
            FrontPanel_GenesisLEDSet((vegascounter >> 6) & 3, (vegascounter & 0xF), (vegascounter >> 8) & 1, 1);
            FrontPanel_GenesisLEDSet((vegascounter >> 6) & 3, (vegascounter & 0xF), ~(vegascounter >> 8) & 1, 0);
            if(++vegascounter == 0x400){
                vegascounter = 0;
                vegasstate = 5;
            }
            break;
        case 5:
            for(i=0; i<18; i++){
                FrontPanel_LEDRingSet(i, 0, !(i&1) ? (15 - ((vegascounter >> 6) & 0xF)) : ((vegascounter >> 6) & 0xF));
            }
            FrontPanel_GenesisLEDSet(3 - ((vegascounter >> 6) & 3), (vegascounter & 0xF), (vegascounter >> 8) & 1, 1);
            FrontPanel_GenesisLEDSet(3 - ((vegascounter >> 6) & 3), (vegascounter & 0xF), ~(vegascounter >> 8) & 1, 0);
            if(++vegascounter == 0x400){
                vegascounter = 0;
                if(++vegassub == 2){
                    vegassub = 0;
                    vegasstate = 6;
                }else{
                    vegasstate = 4;
                }
            }
            break;
        case 6:
            for(i=0; i<18; i++){
                FrontPanel_LEDRingSet(i, 1, ((vegascounter >> 6) & 0xF));
            }
            FrontPanel_GenesisLEDSet(((vegascounter >> 6) & 3), (vegascounter & 0xF), 0, ((vegascounter >> 8) & 1) ^ ((vegascounter >> 6) & 1) ^ (vegascounter & 1));
            FrontPanel_GenesisLEDSet(((vegascounter >> 6) & 3), (vegascounter & 0xF), 1, ((vegascounter >> 8) & 1) ^ ((vegascounter >> 6) & 1) ^ (~vegascounter & 1));
            if(++vegascounter == 0x400){
                vegascounter = 0;
                vegasstate = 7;
            }
            break;
        case 7:
            for(i=0; i<18; i++){
                FrontPanel_LEDRingSet(i, 1, 15 - ((vegascounter >> 6) & 0xF));
            }
            FrontPanel_GenesisLEDSet(((vegascounter >> 6) & 3), (vegascounter & 0xF), 0, ((vegascounter >> 8) & 1) ^ ((vegascounter >> 6) & 1) ^ (vegascounter & 1));
            FrontPanel_GenesisLEDSet(((vegascounter >> 6) & 3), (vegascounter & 0xF), 1, ((vegascounter >> 8) & 1) ^ ((vegascounter >> 6) & 1) ^ (~vegascounter & 1));
            if(++vegascounter == 0x400){
                vegascounter = 0;
                if(++vegassub == 1){
                    vegassub = 0;
                    vegasstate = 0;
                }else{
                    vegasstate = 6;
                }
            }
            break;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called each mS from the MIDI task which checks for incoming
// MIDI events. You could add more MIDI related jobs here, but they shouldn't
// consume more than 300 uS to ensure the responsiveness of incoming MIDI.
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_MIDI_Tick(void){
    //Nothing here
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a MIDI package has been received
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package){
    //TODO MIDI input
    DBG("MIDI message received port %d type %d channel %d", port, midi_package.type, midi_package.chn);
    MIOS32_MIDI_SendPackage(UART0, midi_package);
    MIOS32_MIDI_SendPackage(UART1, midi_package);
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called before the shift register chain is scanned
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_SRIO_ServicePrepare(void){
    BLM_X_PrepareRow();
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called after the shift register chain has been scanned
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_SRIO_ServiceFinish(void){
    BLM_X_GetRow();
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a button has been toggled
// pin_value is 1 when button released, and 0 when button pressed
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_DIN_NotifyToggle(u32 pin, u32 pin_value){
    DBG("DIN pin %d changed %d", pin, pin_value);
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when an encoder has been moved
// incrementer is positive when encoder has been turned clockwise, else
// it is negative
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_ENC_NotifyChange(u32 encoder, s32 incrementer){
    FrontPanel_EncoderChange(encoder, incrementer);
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a pot has been moved
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_AIN_NotifyChange(u32 pin, u32 pin_value){
    //Nothing here
}
