/* ========================================
 * Project: Social Robot
 * Course: CSE 564 - Software Design
 * Team: 4
 * University: Arizona State University
 * Author: Sandeep Nadella
 * Initial Version Date: 11/16/2019
 * Version: 0.1
 * ========================================
*/
#include "project.h"


void initializeAllComponenets() {
    RightEyebrow_Start();
    LeftEyebrow_Start();
    EyeBallVertical_Start();
    EyelidGroup_Start();
    BaseJaw_Start();
    LeftEyebrow_Start();
    EyeBallHorizontal_Start();
    Neck_Start();
    Lip_Start();
}

void resetLeftEyebrow() {
    LeftEyebrow_WriteCompare1(1000);
    LeftEyebrow_WriteCompare2(1000);
}

void sadLeftEyebrow() {
    LeftEyebrow_WriteCompare1(1600);
    LeftEyebrow_WriteCompare2(1600);
}

void raisedLeftEyebrow() {
    LeftEyebrow_WriteCompare1(200);
    LeftEyebrow_WriteCompare2(200);
}

void clearLeftEyebrow() {
    LeftEyebrow_WriteCompare1(0);
    LeftEyebrow_WriteCompare2(0);
}

void resetRightEyebrow() {
    RightEyebrow_WriteCompare1(1000);
    RightEyebrow_WriteCompare2(1000);
}

void raisedRightEyebrow() {
    RightEyebrow_WriteCompare1(1600);
    RightEyebrow_WriteCompare2(1600);
}

void sadRightEyebrow() {
    RightEyebrow_WriteCompare1(200);
    RightEyebrow_WriteCompare2(200);
}

void clearRightEyebrow() {
    RightEyebrow_WriteCompare1(0);
    RightEyebrow_WriteCompare2(0);
}

void moveLowerJawUp() {
    BaseJaw_WriteCompare1(800);
}
void moveNeckDown() {
    Neck_WriteCompare1(1500);
    Neck_WriteCompare2(500);
    //Close the jaw
    moveLowerJawUp();
}

void moveNeckCenter() {
    Neck_WriteCompare1(1000);
    Neck_WriteCompare2(1000);
}

void moveNeckUp() {
    Neck_WriteCompare1(500);
    Neck_WriteCompare2(1500);
}

void resetJaw() {
    BaseJaw_WriteCompare1(200);
}

void moveBaseCenter() {
    BaseJaw_Start();
    BaseJaw_WriteCompare2(1500);
    CyDelay(2000);
    BaseJaw_Stop();
}

void moveBaseRight() {
    BaseJaw_WriteCompare2(500);
}

void moveBaseLeft() {
    BaseJaw_WriteCompare2(2500);
}
void moveLowerJawDown() {
    BaseJaw_WriteCompare1(600);
}

void moveHeadRight() {
    Neck_WriteCompare1(1500);
    Neck_WriteCompare2(1500);
}

void moveHeadLeft() {
    Neck_WriteCompare1(500);
    Neck_WriteCompare2(500);
}

void resetAllServoPositions() {
    raisedLeftEyebrow();
    raisedRightEyebrow();
    
    moveBaseCenter();
    
    moveNeckDown();
    
    EyeBallVertical_WriteCompare1(200);
    EyelidGroup_WriteCompare1(200);
    LeftEyebrow_WriteCompare1(200);
    EyeBallHorizontal_WriteCompare1(200);
    Lip_WriteCompare1(200);
    
    EyeBallVertical_WriteCompare2(200);
    EyelidGroup_WriteCompare2(200);
    LeftEyebrow_WriteCompare2(200);
    EyeBallHorizontal_WriteCompare2(200);
    Lip_WriteCompare2(200);
}

void stopAllComponents() {
    RightEyebrow_Stop();
    LeftEyebrow_Stop();
    EyeBallVertical_Stop();
    EyelidGroup_Stop();
    BaseJaw_Stop();
    LeftEyebrow_Stop();
    EyeBallHorizontal_Stop();
    Neck_Stop();
    Lip_Stop();
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Initialize the Components
    initializeAllComponenets();
    
    //resetAllServoPositions();
    moveNeckCenter();
    
    // Actions
    while(1) {
        sadLeftEyebrow();
        sadRightEyebrow();
        CyDelay(3000);
        raisedLeftEyebrow();
        raisedRightEyebrow();
        CyDelay(3000);
        moveNeckDown();
        CyDelay(5000);
        moveNeckUp();
        CyDelay(5000);
        moveNeckCenter();
        CyDelay(5000);
        moveLowerJawDown();
        CyDelay(6000);
        moveLowerJawUp();
        CyDelay(6000);
        moveHeadLeft();
        CyDelay(6000);
        moveHeadRight();
        CyDelay(6000);
        moveBaseRight();
        CyDelay(6000);
        moveBaseCenter();
        CyDelay(6000);
        moveBaseLeft();
        CyDelay(6000);
        moveBaseCenter();
        CyDelay(6000);
    }
    
    stopAllComponents();
    
}


/* [] END OF FILE */
