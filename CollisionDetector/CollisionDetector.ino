

// unsigned char waveToggle = 0x00;
// unsigned char pulseCount = 0;


// Echo Pin
static const int ECHO_PIN = 4;

// Trigger Pin
static const int TRIGGER_PIN = 5;

static const int BUZZER_PIN = 3;
static const int LED_PIN = 13;

static const int DISTANCE_TO_BEEP = 200;

 


DeclareTaskLoop(BeepManager);
DeclareTaskLoop(Beeper);
DeclareTaskLoop(DistanceMeter);
DeclareTaskLoop(SerialPrinter);



int distanceOnBeep = 0;

int distance = 0;



void setup() { 
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);

    Serial.begin(19200);


    CreateTaskLoop(BeepManager, LOW_PRIORITY);
    CreateTaskLoop(DistanceMeter, LOW_PRIORITY);
    CreateTaskLoop(SerialPrinter, LOW_PRIORITY);

    
    Serial.println("Start");


    // DDRD  |=  B00001000;


    // TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); // 高速PWM

    // TCCR2B = _BV(CS21) |_BV(CS20) | _BV(WGM22);    // 分周1/64

    // OCR2A = 63;
    // OCR2B = 0;

    // //タイマー割り込み開始
    // //TIMSK2 |= _BV(TOIE2);

}

void loop(){

    // digitalWrite(TRIGGER_PIN, LOW); 
    // delayMicroseconds(2); 
    // digitalWrite(TRIGGER_PIN, HIGH ); //超音波を出力
    // delayMicroseconds( 10 ); //
    // digitalWrite( TRIGGER_PIN, LOW );
    // duration = pulseIn( ECHO_PIN, HIGH, 60000 ); //センサからの入力
    // if (duration > 0) {
    //     // duration = duration / 2; //往復距離を半分にする
    //     // distance = duration * 0.034; // 音速を340m/sに設定; duration * 340 * 100 / 1000000
        
    //     distance = duration / 58;

    //     if(distance < DISTANCE_TO_BEEP){
    //         tone(BUZZER_PIN, 4000);
    //     }
    //     else{
    //         noTone(BUZZER_PIN);
    //     }
            
    //     Serial.print("Distance:");
    //     Serial.print(distance);
    //     Serial.println(" cm");
    // }
    // //delay(500);

    // // Serial.println(duration);
    
}



TaskLoop(SerialPrinter){

    Serial.print("Distance:");
    Serial.print(distance);
    Serial.println(" cm");
    DelayWithBlocked(50);
}



TaskLoop(DistanceMeter) {

    unsigned long duration = 0;

    EnterCritical();
    {
        
        // 超音波を出力
        digitalWrite(TRIGGER_PIN, LOW); 
        delayMicroseconds(2);
        digitalWrite(TRIGGER_PIN, HIGH );
        delayMicroseconds( 10 );
        digitalWrite( TRIGGER_PIN, LOW );

        // センサからの入力
        duration = pulseIn( ECHO_PIN, HIGH, 60000);
        if(duration > 0){
            // (duration(us) / 2 / 1000000)(s) * 340
            distance = duration / 58;
        }
        else{
            distance = -1;
        }

    }
    ExitCritical();
    // Yield();
    DelayWithBlocked(50);


    // if(distance < DISTANCE_TO_BEEP){
    //     tone(BUZZER_PIN, 4000);
    // }
    // else{
    //     noTone(BUZZER_PIN);
    // }


    //delay(500);

    // Serial.println(duration);
    
}

int CalculateBeeperDurationTime(int distance){
    if(distance < 0 && distance > DISTANCE_TO_BEEP){
        return 1000;
    }

    double rate = 1.0 - ((DISTANCE_TO_BEEP - distance) / (double)DISTANCE_TO_BEEP);
    rate *= rate;

    int duration = (int)(rate * 1000);
    return duration < 50 ? 50 : duration;
}


TaskLoop(BeepManager){
    
    if((distance > 0) && (distance < DISTANCE_TO_BEEP)){

        if(Beeper == NULL){
            CreateTaskLoop(Beeper, LOW_PRIORITY);
            // Serial.println('A');
        }
    }


    else{
        if(Beeper != NULL){
            DeleteTask(Beeper);
            Beeper = NULL;

                    
            noTone(BUZZER_PIN);
            digitalWrite(LED_PIN, LOW);
        }
    }

    DelayWithBlocked(10);
}

TaskLoop(Beeper){

    int duration = CalculateBeeperDurationTime(distance);

    DelayWithBlocked(duration);

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 4000);

    DelayWithBlocked(duration / 1);
    
    noTone(BUZZER_PIN);
    digitalWrite(LED_PIN, LOW);
}











// ### 過去の遺産 でも残す ###########################################
// ISR(TIMER2_OVF_vect){
 
//     // // High
//     // if(waveToggle){
//     //     waveToggle ^= 0x01;


//     //     OCR2A = 6;
//     //     OCR2B = 2;
//     // }

//     // // Low
//     // else {
//     //     pulseCount++;
//     //     if(pulseCount > 10){
//     //         pulseCount = 0;
            
                    
//     //         OCR2A = 63;
//     //         OCR2B = 63;

//     //         waveToggle ^= 0x01;
//     //     }
//     // }

// }

// ISR(TIMER2_COMPB_vect) {

// }
