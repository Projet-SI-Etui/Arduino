// Définitions pour le moteur
int PWM = 4;
int in1 = 3;
int in2 = 2;

// Définition des broches pour les LED
int ledVerte = 9;
int ledRouge = 10;
int ledOrange = 11;

// Définition des boutons
int boutonAvant = 5;  // broche pour le bouton avancer
int boutonStop = 6;   // broche pour le bouton stop
int boutonArriere = 7; // broche pour le bouton reculer

// Définition du capteur d'intensité (à ajuster avec Ayoub)
int CapteurIntensite = A0;

void setup() {
  // Initialiser le moniteur moteur
  Serial.begin(9600);

  // Configurer le moteur en sortie
  pinMode(PWM, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Mettre les boutons en entrée
  pinMode(boutonAvant, INPUT);
  pinMode(boutonStop, INPUT);
  pinMode(boutonArriere, INPUT);

  // Configurer les LED en sortie
  pinMode(ledVerte, OUTPUT);
  pinMode(ledRouge, OUTPUT);
  pinMode(ledOrange, OUTPUT);

  // Configurer le capteur d'intensité en entrée
  pinMode(CapteurIntensite, INPUT);

  analogWrite(PWM, 0);  // Mettre le PWM à 0V au début
}

void loop() {
  // Lecture du bouton avant
  if (digitalRead(boutonAvant) == LOW) {
    // Avancer
    analogWrite(PWM, 255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    // Allumer la LED verte
    digitalWrite(ledVerte, HIGH);
    digitalWrite(ledRouge, LOW);
    digitalWrite(ledOrange, LOW);

    // Mesurer le courant
    int capteur = analogRead(CapteurIntensite);

    // Si le courant dépasse un certain seuil, arrêter le moteur
    if (capteur > 10) {
      analogWrite(PWM, 0);
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(ledVerte, LOW);
      digitalWrite(ledRouge, HIGH);
      digitalWrite(ledOrange, LOW);
    }
  }

  // Lecture du bouton stop
  else if (digitalRead(boutonStop) == LOW) {
    // Arrêter
    analogWrite(PWM, 0);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    // Allumer la LED rouge
    digitalWrite(ledVerte, LOW);
    digitalWrite(ledRouge, HIGH);
    digitalWrite(ledOrange, LOW);
  }

  // Lecture du bouton arrière
  else if (digitalRead(boutonArriere) == LOW) {
    // Reculer jusqu'à ce que le capteur d'intensité atteigne un seuil
    while (true) {
      analogWrite(PWM, 255);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);

      // Allumer la LED orange
      digitalWrite(ledVerte, LOW);
      digitalWrite(ledRouge, LOW);
      digitalWrite(ledOrange, HIGH);

      // Mesurer le courant
      int capteur = analogRead(CapteurIntensite);

      // Si le courant dépasse un certain seuil, arrêter le moteur
      if (capteur > 10) {
        analogWrite(PWM, 0);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(ledOrange, LOW);
        digitalWrite(ledVerte, LOW);
        digitalWrite(ledRouge, HIGH);
        break;
      }

      delay(100); // Ajustez si nécessaire
    }
  }
}
