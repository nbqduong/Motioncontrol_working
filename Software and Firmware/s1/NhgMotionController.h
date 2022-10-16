#pragma once
#ifndef _NhgMotionController_library_h
#define _NhgMotionController_library_h

#ifdef NHGMOTIONCONTROLLER_EXPORTS
#define NHGMOTIONCONTROLLER_API __declspec(dllexport)
#else
#define NHGMOTIONCONTROLLER_API __declspec(dllimport)
#endif

#endif

#include <windows.h>
#include <iostream>

extern "C" {
	//must run first for get USB infos
	NHGMOTIONCONTROLLER_API INT32 NhgIsOpen(wchar_t* Manufacturer, wchar_t* Product, wchar_t* SerialNumber);

	NHGMOTIONCONTROLLER_API INT32 NhgDrvRel(INT32 InitSpeed, INT32 Speed, INT32 Acc, INT32 Jerk, INT32 Pos, INT32 Dec);

	NHGMOTIONCONTROLLER_API INT32 NhgDrvAbs(INT32 InitSpeed, INT32 Speed, INT32 Acc, INT32 Jerk, INT32 Pos, INT32 Dec);

	NHGMOTIONCONTROLLER_API INT32 NhgVelDrv(INT32 Speed);

	NHGMOTIONCONTROLLER_API INT32 NhgJogDrv(INT32 Speed, INT32 Acc, INT32 Dec);
	/*Over Drive changing speed value
	Input >0 increase speed, <0 decrease speed*/
	NHGMOTIONCONTROLLER_API INT32 NhgSpdChg(INT32 ChangeValue);

	/*Over Drive increase speed value,
	Input >=0*/
	NHGMOTIONCONTROLLER_API INT32 NhgSpdInc(INT32 IncreaseValue);

	/*Over Drive decrease speed value, 
	Input >=0*/
	NHGMOTIONCONTROLLER_API INT32 NhgSpdDec(INT32 DecreaseValue);
	
	NHGMOTIONCONTROLLER_API INT32 NhgMode(INT16 Mode1, INT16 Mode2, INT16 Mode3);

	NHGMOTIONCONTROLLER_API INT32 NhgIoSetup(INT16 Mode1, INT16 Mode2);

	NHGMOTIONCONTROLLER_API INT32 NhgIoGOutCtr(UINT16 IoState);

	NHGMOTIONCONTROLLER_API INT32 NhgLedCtr(UINT16 LEDs);

	NHGMOTIONCONTROLLER_API INT32 NhgEcho(INT32* InitSpeed, INT32* Speed, INT32* Acc, INT32* Jerk, INT32* Pos, INT32* Dec);

	/*Get 3 basic status of drive: Control Pos, Real Pos, Control Vel*/
	NHGMOTIONCONTROLLER_API INT32 NhgStatusGetBasDrv(UINT32* CrlPos, UINT32* RealPos, UINT32* CrlVel);
	
	/*Get initialize Parameter: Stop position, Vel, Acc*/
	NHGMOTIONCONTROLLER_API INT32 NhgMotGetParaLoad(UINT32* InitPos, UINT32* InitVel, UINT32* InitAcc);
	
	/*Get Real Pos (encoder)*/
	NHGMOTIONCONTROLLER_API INT32 NhgStatusGetActPos(UINT32* RealPos);
	
	/*Get Control Pos (command pos)*/
	NHGMOTIONCONTROLLER_API INT32 NhgStatusGetCmdPos(UINT32* CrlPos);

	NHGMOTIONCONTROLLER_API INT32 NhgMoveDecStop();

	NHGMOTIONCONTROLLER_API INT32 NhgMoveInsStop();
	
	NHGMOTIONCONTROLLER_API INT32 NhgSetLpRp(INT32 LogicalPos, INT32 RealPos);

	NHGMOTIONCONTROLLER_API INT32 NhgSetLp(INT32 LogicalPos);

	NHGMOTIONCONTROLLER_API INT32 NhgSetRp(INT32 RealPos);

	NHGMOTIONCONTROLLER_API INT32 NhgChangeVel(INT32 ChangeValue);

	NHGMOTIONCONTROLLER_API INT32 NhgDrvWait();
}

/*------SET MODE PARARMETER---------*/
/*---------MODE3 PARAMETER----------*/
//auto or manl deceleration
#define MANLDEC				0x0001
#define AUTODEC				0x0000

//acc = dec? (symmetry)
//if non-symmetry, must use MANLDEC 0x0001
#define DECSYMM				0x0000
#define DECNONSYMM			0x0002

//scurve or trape acc/dec
#define SCURVE				0x0004
#define TRAPEZOID			0X0000

//pulse and dir output mode
// 2 pulse for each dir
// 1 pulse 1 dir
// quad pulse quad edge
// quad pulse double edge
#define INDEPENDENT			0x0000
#define ONEPULONEDIR		0x0008
#define QUADPULQUADEDGE		0x0010
#define QUADPULDBLEDGE		0x0018

//pulse output positive or negative logic
#define POSPULLOGICAL		0x0000
#define NEGPULLOGICAL		0x0020

//Only effect on ONEPULONEDIR mode
//mode1 +dir low, -dir high
//mode2 +dir high, -dir low
#define DIRPINMODE1			0x0000
#define DIRPINMODE2			0X0040

//invert (swap) signal output pin
#define NOINVOUTPUT			0x0000
#define INVOUTPUT			0x0080

//encoder reader mode
#define ENCQUADPULQUADEDGE	0x0000
#define ENCQUADPULDBLEDGE	0x0100
#define ENCQUADPULSGLEDGE	0x0200
#define ENCUPDOWNPUL		0x0300

//encoder input positive or negative logic
#define POSENCLOGICAL		0x0000
#define NEGENCLOGICAL		0x0400

//invert (swap) encoder input pin
#define NOINVENCINPUT		0x0000
#define INVENCINPUT			0x0800

//invert (swap) limit input pin
#define NOINVLMTINPUT		0x0000
#define INVLMTINPUT			0x1000

//enable prevent triangle profile in linear acc
#define	ENASTOPTRI			0x0000
#define DISSTOPTRI			0x2000

//setting once or repeat timer
#define	ONCETIMER			0x0000
#define REPEATTIMER			0x4000
/*---------END MODE3 PARAMETER----------*/


/*----------SETUP IO PARAMETER----------*/
/*---------------SETTING 1--------------*/
/* Sua code:*/
/* PIO4, PIO5 sua mac dinh thanh input cho chuc nang Jog*/
/* PIO2, PIO3 mac dinh la input tu servo to MCX*/
/* PIO6, PIO7 mac dinh la output tu MCX to servo*/
/* PIO0, PIO1 hien noi thang voi RD3, RD4 chua setup chuc nang: du tinh set lam output Drive va Error */

/*PIO 0*/
//General purpose input
#define PIO0GIN				0x0000
//General purpose output
#define PIO0GOUT			0x0001
//Drive status output
#define PIO0SOUT			0x0002
//Synchronous pulse output
#define PIO0POUT			0x0003

/*PIO 1*/
//General purpose input
#define PIO1GIN				0x0000
//General purpose output
#define PIO1GOUT			0x0004
//Drive status output
#define PIO1SOUT			0x0008
//Synchronous pulse output
#define PIO1POUT			0x000C

/*PIO 2*/
//General purpose input
#define PIO2GIN				0x0000
//General purpose output
#define PIO2GOUT			0x0010
//Drive status output
#define PIO2SOUT			0x0020
//Synchronous pulse output
#define PIO2POUT			0x0030

/*PIO 3*/
//General purpose input
#define PIO3GIN				0x0000
//General purpose output
#define PIO3GOUT			0x0040
//Drive status output
#define PIO3SOUT			0x0080
//Synchronous pulse output
#define PIO3POUT			0x00C0

/*PIO 4*/
//General purpose input
#define PIO4GIN				0x0000
//General purpose output
#define PIO4GOUT			0x0100
//Drive status output
#define PIO4SOUT			0x0200
//Synchronous pulse output
#define PIO4POUT			0x0300

/*PIO 5*/
//General purpose input
#define PIO5GIN				0x0000
//General purpose output
#define PIO5GOUT			0x0400
//Drive status output
#define PIO5SOUT			0x0800
//Synchronous pulse output
#define PIO5POUT			0x0C00

/*PIO 6*/
//General purpose input
#define PIO6GIN				0x0000
//General purpose output
#define PIO6GOUT			0x1000
//Drive status output
#define PIO6SOUT			0x2000
//Synchronous pulse output
#define PIO6POUT			0x3000

/*PIO 7*/
//General purpose input
#define PIO7GIN				0x0000
//General purpose output
#define PIO7GOUT			0x4000
//Drive status output
#define PIO7SOUT			0x8000
//Synchronous pulse output
#define PIO7POUT			0xC000
/*------------END SETTING 1--------------*/
/*----------------SETTING 2--------------*/
/*Sync Pulse Output*/
//Logical level of sync pulses
//PIO0 positive logical pulse
#define P0LPOS				0x0000
//PIO0 negative logical pulse
#define P0LNEG				0x0001
//PIO1 positive logical pulse
#define P1LPOS				0x0000
//PIO1 negative logical pulse
#define P1LNEG				0x0002
//PIO2 positive logical pulse
#define P2LPOS				0x0000
//PIO2 negative logical pulse
#define P2LNEG				0x0004
//PIO3 positive logical pulse
#define P3LPOS				0x0000
//PIO3 negative logical pulse
#define P3LNEG				0x0008
//Sync pulse width
//125 nanosec
#define PW125N				0x0000
//312 nanosec
#define PW312N				0x0001
//1 microsec
#define PW1U				0x0020
//4 microsec
#define PW4U				0x0030
//16 microsec
#define PW16U				0x0040
//64 microsec
#define PW64U				0x0050
//256 microsec
#define	PW256U				0x0060
//1 milisec
#define PW1M				0x0070
//Stop sync action at error or not
//NOT stop at error
#define ERRSYNCNOTSTOP		0x0000
//STOP at error
#define ERRSYNCSTOP			0x0080
//Setting external input signal for driving
//Disalbe drive by external signal (JOG)
#define DISJOGMOD			0x0000
//Continuous driving JOG mode
#define CONTJOGMOD			0x0100
//Relative position driving JOG mode
#define RELJOGMOD			0x0200
//MPG mode
#define MPGJOGMOD			0x0300
//Logical level of split pulse output
//Positive split pulse
#define SPLLPOS				0x0000
//Negative split pulse
#define SPLLNEG				0x0400
//With or Without starting pulse of split pulse output
//Without
#define SPLNOSTRPUL			0x0000
//With
#define SPLSTRPUL			0x0800
/*------------END SETTING 2--------------*/
/*--------END SETUP IO PARAMETER---------*/

/*--GENERAL IO OUTPUT CONTROL PARAMETER--*/
#define PIO0L				0x0000
#define PIO1L				0x0000
#define PIO2L				0x0000
#define PIO3L				0x0000
#define PIO4L				0x0000
#define PIO5L				0x0000
#define PIO6L				0x0000
#define PIO7L				0x0000

#define PIO0H				0x0001				
#define PIO1H				0x0002
#define PIO2H				0x0004
#define PIO3H				0x0008
#define PIO4H				0x0010
#define PIO5H				0x0020
#define PIO6H				0x0040
#define PIO7H				0x0080
/*-------END IO CONTROL PARAMETER-------*/

/*------ON BOARD LED CONTROL--------*/
//SET LED ON
#define LED2H				0x0008		
#define LED3H				0x0010
#define LED4H				0x0020
#define LED5H				0x0040
//SET LED OFF
#define LED2L				0x0000		
#define LED3L				0x0000
#define LED4L				0x0000
#define LED5L				0x0000

/*-------END ON BOARD LED CONTROL-------*/