//
// retour loop
// VoLAB
// mai 2018
// CC-0
//
#define C1PIN 5
#define C2PIN 4
#define C3PIN 3

#define RELAISPIN 2
#define LEDRELAIS 13

int state;

void setup(){
    pinMode( C1PIN, INPUT_PULLUP );
    pinMode( C2PIN, INPUT_PULLUP );
    pinMode( C3PIN, INPUT_PULLUP );
    pinMode( RELAISPIN, OUTPUT);
    pinMode( LEDRELAIS, OUTPUT);
	Serial.begin(9600);
	Serial.println("pret");
	
}

void loop(){
    // inversées à cause du INPUT_PULLUP
    int C1 = !digitalRead(C1PIN);
    int C2 = !digitalRead(C2PIN);
    int C3 = !digitalRead(C3PIN);
    char chaine[256];
//    sprintf( chaine, "C1 : %d, C2 : %d, C3 : %d", C1, C2, C3);
    sprintf( chaine , "etat : %d", state);
    Serial.println( chaine );
	
    //Machine d'état
    switch (state){
        case 0:
            if (C1) state = 1;
            if (C3) state = 6;
        break;
        case 1: if (!C1) state = 2; break;
        case 2: if (C2) state = 3 ; break;
        case 3: if (!C2) state = 4 ; break;
        case 4: if (C3) state = 5 ; break;
        case 5: if (!C3) state = 0 ; break; //le train est sorti en C3
        case 6: if (!C3) state = 7 ; break;
        case 7: if (C2) state = 8 ; break;
        case 8: if (!C2) state = 9 ; break;
        case 9: if (C1) state = 10 ; break;
        case 10: if (!C1) state = 0 ; break;
        default:
            state = 0;
        break; 
    }
    
    //Décodage des états
    if ( state == 4 | state == 6 ){
      digitalWrite( RELAISPIN, HIGH);
      digitalWrite( LEDRELAIS, HIGH);
    }
    if (state == 5 | state == 9){
      digitalWrite( RELAISPIN, LOW);
      digitalWrite( LEDRELAIS, LOW);
    }
    
}
