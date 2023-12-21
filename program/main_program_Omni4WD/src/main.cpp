#include <EEPROM.h>
//#define _NAMIKI_MOTOR
#include <MotorWheel.h>
#include <Omni4WD.h>
#include <PID_Beta6.h>
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include <SONAR.h>

/*
************************************************************************************
                                     Sonar:0x12
                           ------------------------------
                          |                             |
                        M3|                             |M2
                          |                             |
                          |                             |
                          |                             |
                Sonar:0x13|                             |Sonar:0x11
                          |                             |
                          |                             |Power Switch
                          |                             |
                          |                             |
                          -------------------------------
                          |                             |
                        M4|                             |M1
                          |                             |
                          -------------------------------
                                    Sonar:0x14                          
************************************************************************************
*/


irqISR(irq1,isr1);
MotorWheel wheel1(3,2,4,5,&irq1);
irqISR(irq2,isr2);
MotorWheel wheel2(11,12,14,15,&irq2);

irqISR(irq3,isr3);
MotorWheel wheel3(9,8,16,17,&irq3);

irqISR(irq4,isr4);
MotorWheel wheel4(10,7,18,19,&irq4);

Omni4WD Omni(&wheel1,&wheel2,&wheel3,&wheel4);

SONAR sonar11(0x11),sonar12(0x12),sonar13(0x13),sonar14(0x14);
unsigned short distBuf[4];

unsigned char sonarsUpdate() {
    static unsigned char sonarCurr = 1;
    if(sonarCurr==4) sonarCurr=1;
    else ++sonarCurr;
    if(sonarCurr==1) {        
        distBuf[1]=sonar12.getDist();  
        sonar12.showDat();     
        sonar12.trigger();        
    } else if(sonarCurr==2) {
        distBuf[2]=sonar13.getDist();
        sonar13.showDat();
        sonar13.trigger();
    } else if(sonarCurr==3){
        distBuf[3]=sonar14.getDist();
        sonar14.showDat();
        sonar14.trigger();
    } else {
        distBuf[0]=sonar11.getDist();
        sonar11.showDat();
        sonar11.trigger();
    }
    
    return sonarCurr;
}

void goAhead(unsigned int speedMMPS){
    if(Omni.getCarStat()!=Omni4WD::STAT_ADVANCE) Omni.setCarSlow2Stop(300);
        Omni.setCarAdvance(0);
        Omni.setCarSpeedMMPS(speedMMPS, 300);
}

void turnLeft(unsigned int speedMMPS){
    if(Omni.getCarStat()!=Omni4WD::STAT_LEFT) Omni.setCarSlow2Stop(300);
        Omni.setCarLeft(0);
        Omni.setCarSpeedMMPS(speedMMPS, 300);
}

void turnRight(unsigned int speedMMPS){
    if(Omni.getCarStat()!=Omni4WD::STAT_RIGHT) Omni.setCarSlow2Stop(300);
        Omni.setCarRight(0);
        Omni.setCarSpeedMMPS(speedMMPS, 300);
}

void rotateRight(unsigned int speedMMPS){
    if(Omni.getCarStat()!=Omni4WD::STAT_ROTATERIGHT) Omni.setCarSlow2Stop(300);
        Omni.setCarRotateRight(0);
        Omni.setCarSpeedMMPS(speedMMPS, 300);
}

void rotateLeft(unsigned int speedMMPS){
    if(Omni.getCarStat()!=Omni4WD::STAT_ROTATELEFT) Omni.setCarSlow2Stop(300);
        Omni.setCarRotateLeft(0);
        Omni.setCarSpeedMMPS(speedMMPS, 300);
}

void allStop(unsigned int speedMMPS){
    if(Omni.getCarStat()!=Omni4WD::STAT_STOP) Omni.setCarSlow2Stop(300);
        Omni.setCarStop();
}

void backOff(unsigned int speedMMPS){
  if(Omni.getCarStat()!=Omni4WD::STAT_BACKOFF) Omni.setCarSlow2Stop(300);
        Omni.setCarBackoff(0);
        Omni.setCarSpeedMMPS(speedMMPS, 300);
}

//void(*motion[8])(unsigned int speedMMPS) = {goAhead, turnLeft, rotateRight, rotateLeft, 
    //turnRight, goAhead, rotateRight, backOff};

void(*motion[16])(unsigned int speedMMPS) = {goAhead, turnRight, goAhead, turnRight, 
    turnLeft, goAhead, turnLeft, goAhead,
    rotateRight, rotateRight, turnRight, turnRight,
    rotateLeft, backOff, turnLeft, allStop};
    
unsigned long currMillis=0;
void demoWithSensors(unsigned int speedMMPS,unsigned int distance) {
    unsigned char sonarcurrent = 0;
    if(millis()-currMillis>SONAR::duration + 20) {
        currMillis=millis();
        sonarcurrent = sonarsUpdate();
    }   
    
    if(sonarcurrent == 4){
        unsigned char bitmap = (distBuf[0] < distance);  //right
        bitmap |= (distBuf[1] < distance) << 1;  // back
        bitmap |= (distBuf[2] < distance) << 2;  // left
        bitmap |= (distBuf[3] < distance) << 3;  // front
        
        (*motion[bitmap])(speedMMPS);
        Serial.println(bitmap);
    }
    
    Omni.PIDRegulate();
}

void setup() {
    delay(2000);

    Serial.println("Start setup - PWM 31250Hz");  
    TCCR1B=TCCR1B&0xf8|0x01;    // Pin9,Pin10 PWM 31250Hz
    TCCR2B=TCCR2B&0xf8|0x01;    // Pin3,Pin11 PWM 31250Hz

    delay(2000);
    
    SONAR::init(13);     
    Omni.PIDEnable(0.35,0.02,0,10);

    Serial.println("Start test");
    // Omni.setCarMove(70,0,0.1);
    // delay(2000);
    // Omni.setCarMove(0,0,0);
    // delay(2000);
    Serial.println("Go ahead");
    goAhead(100);
    delay(2000);
    Serial.println("All stop");
    allStop(0);
    delay(2000);
    Serial.println("End test");
}

void loop() {
    // TODO: implement communication with the high-level system
}


