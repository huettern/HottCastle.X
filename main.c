/*****************************************************************************
 * Projekt:       eLevel
 * Zielsystem:		eLevel Hardware
 * Programmtyp:		Main-Modul
 * Beschreibung:	**X**
 * Compiler:      HITECH ANSI-C-Compiler PICC-Lite Ver. 9.83
 * Filename:      main.c
 * Version:       0.1
 * Autor:         Noah Huetter
 ****************************************************************************/

#include "htc.h"	/* Compiler-Grundfunktionen */
#include "always.h"	/* Datentypenerweiterungen f�r Delayfunktionen */
#include "delay.h"	/* Headerdatei Delayfunktionen */


/*****************************************************************************
 * KONFIGURATION CONTROLLER
 ****************************************************************************/

__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & 
         CPD_OFF & BOREN_ON & CLKOUTEN_OFF & IESO_ON & FCMEN_ON);
__CONFIG(WRT_OFF & PLLEN_OFF & STVREN_ON & BORV_LO & LVP_ON);

/*****************************************************************************
 * DEFINE I/Os
 ****************************************************************************/
typedef unsigned char tByte;
typedef unsigned int tSWord;

#define EVER ;;
#define PIN(x,y,z) static bit x @ ((unsigned) &y*8+z)
PIN(PWM, PORTC, 3);

//defines for statemachine
#define IDLE  0
#define CHECK_REQUEST 1
#define TRANSMIT  2
#define CALCULATE_BUFF 3
#define READ_ANALOG 4
#define DEBUG 99

#define IDLE_LINE_TIME 6 //[ms]
#define TX_DATA_INTERVAL 3 //[ms]

tByte CurrentState = IDLE; //current state machine state

tByte TxBuffer[37] = 0; //transmit buffer

tSWord NewMeasurement = 0; //for new measurements
tByte CurrentDataInState = 0; /*indicates, which measurement is stored in
                               * NewMeasurement: 1 = RESET
                               * 2 = Calibration Measurement should be 1ms
                               * 3 = Battery Voltage
                               * 4 = Ripple Voltage
                               * 5 = Current
                               * 6 = Throttle
                               * 7 = Output Power
                               * 8 = RPM
                               * 9 = BEC Voltage
                               * 10 = BEC Current
                               * 11 = Temp (if linear sensor installed)
                               * 12 = Temp (if NTC sensor is installed) */

tByte EdgeKeeper = 0; //keeps the state of the last input edge
tByte bRXCount = 0;
tByte bTransmitData = 0;
tByte bDummy = 0;
tByte bRxMode = 0;      //first received byte
tByte bRxModuleID = 0;  //second received byte

void MAIN_fInit(void);

/*****************************************************************************
 * HAUPTPROGRAMMBEREICH
 ****************************************************************************/

void main(void)
{
  MAIN_fInit(); //init all rewuired peripherals
  CurrentState = DEBUG;

  /*start endless loop*/
  for(EVER)
  {
//    RC4 ^= 1;
    if(CurrentState == IDLE)
    {
    /*Execute Actions*/

    /*Check exit condition*/
      
    }
    else if(CurrentState == CHECK_REQUEST)
    {

    }
    else if(CurrentState == TRANSMIT)
    {

    }
    else if(CurrentState == CALCULATE_BUFF)
    {

    }
    else if(CurrentState == READ_ANALOG)
    {

    }
    else if(CurrentState == DEBUG)
    {
      
    
      if(bTransmitData == 1) //RCREG == 0x8D
      {
        GIE = 0;
        bTransmitData = 0;
        RCIE = 0;
        CREN = 0;
        //bump raw over Tx
        TXEN = 1;
        fDelay_ms(IDLE_LINE_TIME);

        TXREG = 0x7C;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x8D;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;  //alarm
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0xD0;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;  //alarm invers 1
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;  //alarm invers 2
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00; //13
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00; //17
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00; //19
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;//21
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;//30
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;//40
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x00;
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x7D;//end of transmission
        fDelay_ms(TX_DATA_INTERVAL);TXREG = 0x70;//CHECKSUM
        fDelay_ms(TX_DATA_INTERVAL);

        TXEN = 0;
        RCIF = 0;
        RCIE = 1;
        CREN = 1;
        GIE = 1;
      }



 /*     if(NewMeasurement) //check if a new measurement was made
      {
        //bump raw over Tx
        TXEN = 1;
        TXREG = (NewMeasurement >> 8) & 0x00ff;
        TXREG = NewMeasurement && 0x00ff;
        NewMeasurement = 0;
      }
   */



    }
  }

}

/*****************************************************************************
 * UNTERPROGRAMMBEREICH
 ****************************************************************************/

/*==========================================================================*/
void MAIN_fInit(void)
/*--------------------------------------------------------------------------
Beschreibung:
Initialisierung der I/O-Ports.
Keine Parameteruebergabe.
Kein Rueckgabewert.
============================================================================*/
{
  //config clock
  OSCCON = 0b01111010; //HF Int Osc, No PLL, -> Clock = 16Mhz
  while(!HFIOFR); //wait for clock to be ready

  //config I/Os
  PORTA = 0x00; //clear all inputs
  PORTC = 0x00;
  TRISC3 = 1;   //CCP3 Pin is Input
  TRISC5 = 1;   //RX Pin is input
  ANSC3 = 0;    //PWM: digital Input

//  TRISC4 = 0;
  
  //config Serial Port
  TXSTA = 0x00; //disable transmit, asynchronus mode, low speed
  RCSTA = 0x80; //enable module, disable receive
  BAUDCON = 0x00; //non inverted output
  BRG16 = 0;  //8bit prescale
  SPBRG = 12; // = (16MhZ/Baud)/64 -1

  //config Capture Timer 1
  T1GCON = 0x00;  //disable Timer output
  T1CON = 0b00000000; //tick = 1/(Sysclock/4) = 1/(4MHz) 250ns, STOP timer
  
  //config Capture to reset timer at pos. edge & read it on neg. edge
  CCP2IE = 0; //disable interrupt
  CCP2CON = 0x05; //set capture module 2 to rising edge
  //CCP2CON = 0x04; //set capture module 2 to falling edge

  //config Compare to trigger to 5ms
  CCP3IE = 0; //disable interrupt
  CCP3CON = 0x0A; //set compare module 3 to compare without output
  CCPR3H = 0x4E;  //set compare value to 20'000 -> 5ms
  CCPR3L = 0x20;  //value = t / 250E-9

  //config ADC TODO

  
  //config Timer for a tick TODO

  //enable interrupts for all modules
  PIE1 = 0; //disable all peripheral interrupts
  PIE2 = 0;
  PIE3 = 0;
  CCP2IF = 0; //clear all interrupt flags
  CCP3IF = 0;
  CCP2IE = 1; //enable interrupt on Capture/Compare modules 1-3
  CCP3IE = 1;
  RCIE = 1;
  CREN = 1; //enablge receive interrupt
  INTCON = 0x40;  //enable only peripheral interrupts
  GIE = 1;  //enable global interrupts

} /* End of fPortInitialierung */

void interrupt fCCPInterrupt (void)
/*--------------------------------------------------------------------------
 Interrupt called on one of the CCP Modules
============================================================================*/
{
  if(CCP2IF == 1)
  /*edge got captured*/
  {
    CCP2IE = 0; //disable interrupts
    CCP2IF = 0; //clear flag
    if(CCP2CON == 0x04)
    /*falling edge on input*/
    {
      if(EdgeKeeper == 1) //only if previous edge was positive
      {
        NewMeasurement = ((CCPR2H << 8) | CCPR2L); //save measurement
        fDelay_big_us(250);  //wait for the neg. "tick" to rise again
        CCP2IF = 0; //clear flag
        EdgeKeeper  = 0;
      }
      else
      {
        EdgeKeeper = 1;
        CCP2CON = 0x05;
      }
    }
    else if(CCP2CON == 0x05)
    /*rising edge*/
    {
      EdgeKeeper = 1;
      TMR1 = 0; //reset
      TMR1ON = 1; //start
      CCP2CON = 0x04; //next interrupt on falling edge
    }
    CCP2IE = 1; //enable interrupts
  }

  else if(CCP3IF == 1)
  /*timer overflows 5ms*/
  {
    CCP3IE = 0; //disbable interrupt
    CCP3IF = 0; //clear flag
    CurrentDataInState = 1; //we are now on the first state of data in
    TMR1ON = 0; //stop timer
    CCP3IE = 1; //enable interrupt
  }
  else if(RCIF)
  //UART receive interrupt
  {
    RCIF = 0; //clear interrupt flag
    if(bRXCount == 0)
    //if this is the first received byte
    {
      bRXCount++;
      bRxMode = RCREG;  //get first received byte
    }
    else if(bRXCount == 1)
    //if this was the second received byte
    {
      bRxModuleID = RCREG;  //get second received byte
      if(bRxMode == 0x80 && bRxModuleID == 0x8D)
      //if GAM is called in binary mode
      {
        CREN = 0; //disable receiver
        /* TODO: RESPECT 5ms IDLE LINE!!!! */
        bTransmitData = 1;  //transmit data
      }
      bRXCount = 0;
    }
  }
}/* End of fCCPInterrupt */


/*****************************************************************************
 * ENDE DES CODES
 ****************************************************************************/

