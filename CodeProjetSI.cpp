// Définitions pour le moteur
int PWM = 11;
int in1 = 12;
int in2 = 13;

int ledRouge = 6;
int ledVert = 7; // ma led = pin 8 du arduino
int boutonAvancerStop = 4;
int boutonReculerStop = 5; // le bouton = pin 4
int boutonMarcheArret = 3;
int timeDelay = 500; // mon temps de delai 

// L'état initial de mon bouton poussoir (ici éteint)
bool buttonState = false; 
bool buttonState2 = false; 
bool buttonState3 = false;
bool recule = false;

int CapteurIntensite = A0;
// Seuil d'intensité
float seuilIntensite = 120; // Mettez ici la valeur de seuil appropriée en Ampères


void setup()
{
  // Initialiser le moniteur moteur
  Serial.begin(9600);

  // Configurer le moteur en sortie
  pinMode(PWM, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(ledRouge, OUTPUT); // init de ma led
  pinMode(boutonAvancerStop, INPUT); // init de mon bouton
  pinMode(ledVert, OUTPUT); // init de ma led
  pinMode(boutonReculerStop, INPUT); // init de mon bouton
  pinMode(boutonMarcheArret, INPUT); // init de mon bouton

  pinMode(CapteurIntensite, INPUT);

  analogWrite(PWM, 0);  // Mettre le PWM à 0V au début
}

// Fonction pour faire clignoter les LEDs deux fois
void clignoterLEDs() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(ledRouge, HIGH);
    digitalWrite(ledVert, HIGH);
    delay(250);
    digitalWrite(ledRouge, LOW);
    digitalWrite(ledVert, LOW);
    delay(250);
  }
}

float mesureIntensite() {
  // Lire la tension à travers le capteur d'intensité
  float tension = analogRead(CapteurIntensite) * (500 / 1023.0);

  // Calculer l'intensité en utilisant la loi d'Ohm (R = 110 ohms)
  float intensite = tension / 0.47;

  return intensite;
}


void loop()
{

// Vérifier l'état du bouton marche/arrêt
  if (digitalRead(boutonMarcheArret) == HIGH && !buttonState3) {
    buttonState3 = true;
    clignoterLEDs(); // Clignoter les LEDs deux fois
    delay(200); // Délai pour éviter les rebonds
  } else if (digitalRead(boutonMarcheArret) == HIGH && buttonState3) {
    buttonState3 = false;
    digitalWrite(PWM, LOW); // Arrêter le moteur
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    clignoterLEDs(); // Clignoter les LEDs deux fois
    delay(200); // Délai pour éviter les rebonds
    return; // Sortir de la boucle loop()
  }

  // Si le programme est désactivé, quitter la boucle loop()
  if (!buttonState3) {
    return;
  }


  // Mesurer l'intensité
  float intensite = mesureIntensite();

  // Si l'intensité dépasse le seuil, arrêter le moteur
  if (intensite > seuilIntensite && recule == false) {
    digitalWrite(PWM, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(ledRouge, LOW);
    digitalWrite(ledVert, HIGH);
    Serial.print(intensite);
    return;
  }


  // condition 1 : bouton appuyé ET état actuel du bouton éteint
  if (digitalRead(boutonAvancerStop) == HIGH && !buttonState)
  {
     // Avancer
    analogWrite(PWM, 255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 


    digitalWrite(ledRouge, HIGH);
    digitalWrite(ledVert, LOW); // j'allume ma led 
    buttonState = !buttonState;  // je change l'état de false à true 
    delay(timeDelay); // je mets un temps de delai 

  }

      // condition 2 : bouton appuyé ET état actuel du bouton allumé
  if (digitalRead(boutonAvancerStop) == HIGH && buttonState)
  {

    // Arrêter
   analogWrite(PWM, 0);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    digitalWrite(ledRouge, LOW);
    digitalWrite(ledVert, HIGH); // j'éteins ma led
    buttonState = !buttonState; // je change l'état du bouton à false
    delay(timeDelay); // je mets un temps de delai
  }
  else if (digitalRead(boutonReculerStop) == HIGH && !buttonState2)
  {

    analogWrite(PWM, 255);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(ledRouge, HIGH);
    digitalWrite(ledVert, LOW); // j'allume ma led 
    buttonState2 = !buttonState2;  // je change l'état de false à true 
    delay(timeDelay); // je mets un temps de delai
    recule = true; 
    delay(700);
    recule = false;
  }


      // condition 2 : bouton appuyé ET état actuel du bouton allumé
  else if (digitalRead(boutonReculerStop) == HIGH && buttonState2)
  {
    // Arrêter
    analogWrite(PWM, 0);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    digitalWrite(ledRouge, LOW);
    digitalWrite(ledVert, HIGH);// j'éteins ma led
    buttonState2 = !buttonState2; // je change l'état du bouton à false
    delay(timeDelay); // je mets un temps de delai
  }
}
