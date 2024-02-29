// def pour le moteur
int PWM = 4;
int in1 = 3;
int in2 = 2;

// def boutons
int boutonAvant = 5;  // broche pour le bouton avancer
int boutonStop = 6;     // broche pour le bouton stop
int boutonArriere = 7; // broche pour le bouton reculer
int boutonOnOff = 8;    // broche pour le bouton on/off

// Capteur de courant à modifier avec Ayoub pcq j'ai pas tout compris mais dans l'idée c'est ca 
int CapteurIntensite = A0;

// Position initiale et actuelle du moteur
int initialPosition = 0;
int currentPosition = 0;

void setup()
{
  // Initialiser le moniteur moteur
  Serial.begin(9600);

  // Mettre le moteur en sortie
  pinMode(PWM, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Mettre les boutons en entrée
  pinMode(boutonAvant, INPUT);
  pinMode(boutonStop, INPUT);
  pinMode(boutonArriere, INPUT);
  pinMode(boutonOnOff, INPUT);

  // Definir le capteur d'intensite en entrée
  pinMode(CapteurIntensite, INPUT);

  analogWrite(PWM, 0);  // Mettre le PWM à 0 donc 0V envoyé au début
}

void loop()
{
  if (digitalRead(boutonOnOff) == LOW) // Si le bouton on/off est enfoncé
  {
    // Lecture des boutons
    if (digitalRead(boutonAvant) == LOW)
    {
      // Avancer
      analogWrite(PWM, 255); // Valeur à modifié au cas où si ça va trop vite
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);

      // Mesurer le courant
      int capteur = analogRead(CapteurIntensite);

      // Si le courant est supérieur à 10 mA par exemple mais ce sera à Yanis et Antoine de voir, arrêter le moteur
      if (capteur > 10)
      {
        analogWrite(PWM, 0);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
      }
    }
    else if (digitalRead(boutonStop) == LOW)
    {
      // Arrêter
      analogWrite(PWM, 0);
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }
    else if (digitalRead(boutonArriere) == LOW)
    {
      // Reculer jusqu'à la position initiale
      while (currentPosition > initialPosition)
      {
        analogWrite(PWM, 255);
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);

        // Mesurer le courant
        int capteur = analogRead(CapteurIntensite);

        // Si le courant est supérieur à 10 mA, arrêter le moteur
        if (capteur > 10)
        {
          analogWrite(PWM, 0);
          digitalWrite(in1, LOW);
          digitalWrite(in2, LOW);
          break;
        }

        delay(100); // Ajustez si nécessaire
        currentPosition--;
      }

      // Arrêter
      analogWrite(PWM, 0);
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }
  }
  else
  {
    // Si le bouton on/off n'est pas enfoncé
    if (currentPosition != initialPosition)
    {
      // Si le moteur n'est pas à sa position initiale, revenir à cette position
      while (currentPosition < initialPosition)
      {
        analogWrite(PWM, 255);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);

        // Mesurer le courant
        int capteur = analogRead(CapteurIntensite);

        // Si le courant est supérieur à 10 mA, arrêter le moteur
        if (capteur > 10)
        {
          analogWrite(PWM, 0);
          digitalWrite(in1, LOW);
          digitalWrite(in2, LOW);
          break;
        }

        delay(100); // Ajustez si nécessaire
        currentPosition++;
      }

      // Arrêter
      analogWrite(PWM, 0);
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }
    else
    {
      // Si le moteur est déjà à sa position initiale, simplement arrêter le moteur
      analogWrite(PWM, 0);
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }
  }
}
