#define NUM_LEDS 4

const int leds[NUM_LEDS]   = {2, 3, 4, 5};
const int botoes[NUM_LEDS] = {8, 9, 10, 11};
const int buzzer = 12;

const int tom[NUM_LEDS] = {262, 330, 392, 523}; 

int sequencia[100];      
int nivel = 0;
const int MAX_NIVEL = 100;

void setup() {
  randomSeed(analogRead(A0)); 
  
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botoes[i], INPUT_PULLUP);
  }
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Memory Game - Pressione qualquer botao para comecar");
}

void loop() {
  aguardarInicio();
  
  reiniciarJogo();
  
  while (true) {
    sequencia[nivel] = random(NUM_LEDS);
    nivel++;
    
    if (nivel > MAX_NIVEL) {
      vitoria();
      break;
    }
    
    mostrarSequencia();
    
    if (!lerJogador()) {
      derrota();
      break;
    }
    
    delay(1000); 
  }
}

void aguardarInicio() {
  while (true) {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (digitalRead(botoes[i]) == LOW) {
        tone(buzzer, 880, 100);
        delay(300);
        return;
      }
    }
  }
}

void mostrarSequencia() {
  Serial.print("Nivel: ");
  Serial.println(nivel);
  
  delay(500);
  for (int i = 0; i < nivel; i++) {
    piscarLed(sequencia[i], 400);
    delay(200);
  }
}

bool lerJogador() {
  for (int i = 0; i < nivel; i++) {
    int botao = aguardarBotao();
    
    if (botao != sequencia[i]) {
      return false; 
    }
  }
  return true; 
}

int aguardarBotao() {
  while (true) {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (digitalRead(botoes[i]) == LOW) {
        piscarLed(i, 200); 
        tone(buzzer, tom[i], 200);
        
        while (digitalRead(botoes[i]) == LOW) {
          delay(10);
        }
        delay(50);
        return i;
      }
    }
  }
}

void piscarLed(int led, int tempo) {
  digitalWrite(leds[led], HIGH);
  tone(buzzer, tom[led], tempo);
  delay(tempo);
  digitalWrite(leds[led], LOW);
  noTone(buzzer);
}

void reiniciarJogo() {
  nivel = 0;
  for (int i = 0; i < MAX_NIVEL; i++) {
    sequencia[i] = 0;
  }
}

void derrota() {
  Serial.println("Voce perdeu! Nivel alcancado: ");
  Serial.println(nivel);
  
  tone(buzzer, 150, 500);
  delay(500);
  noTone(buzzer);
  
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      digitalWrite(leds[i], HIGH);
    }
    delay(200);
    for (int i = 0; i < NUM_LEDS; i++) {
      digitalWrite(leds[i], LOW);
    }
    delay(200);
  }
  delay(2000);
}

void vitoria() {
  Serial.println("Parabens! Voce venceu!");

  int melodia[] = {523, 659, 784, 1047};
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i % NUM_LEDS], HIGH);
    tone(buzzer, melodia[i], 200);
    delay(250);
    digitalWrite(leds[i % NUM_LEDS], LOW);
  }
  noTone(buzzer);
  delay(2000);
}
