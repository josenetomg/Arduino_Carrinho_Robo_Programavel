#include <AFMotor.h>

// Definição dos Motores
AF_DCMotor motor1(1); // Motor na conexão M1
AF_DCMotor motor2(2); // Motor na conexão M2

// Definição de Pinos (Botoes e LEDs)
const int BTN_FRENTE = A0;
const int BTN_TRAS = A1;
const int BTN_ESQ = A2;
const int BTN_DIR = A3;
const int BTN_REC = 2;   // Botão para gravar
const int BTN_PLAY = 13;  // Botão para executar

const int LED_REC = A4;  // LED Gravação
const int LED_PLAY = A5; // LED Execução

// Estrutura de Memória
struct Comando {
  char acao; // 'F', 'B', 'L', 'R'
};

Comando memoria[50]; 
int totalComandos = 0;
bool modoGravacao = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(BTN_FRENTE, INPUT_PULLUP);
  pinMode(BTN_TRAS, INPUT_PULLUP);
  pinMode(BTN_ESQ, INPUT_PULLUP);
  pinMode(BTN_DIR, INPUT_PULLUP);
  pinMode(BTN_REC, INPUT_PULLUP);
  pinMode(BTN_PLAY, INPUT_PULLUP);
  
  pinMode(LED_REC, OUTPUT);
  pinMode(LED_PLAY, OUTPUT);

  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  
  Serial.println("Sistema Pronto. Pressione REC para programar.");
}

void mover(int dir1, int dir2, char tag) {
  motor1.run(dir1);
  motor2.run(dir2);
  
  if (modoGravacao && totalComandos < 50) {
    memoria[totalComandos].acao = tag;
    totalComandos++;
    Serial.print("Gravado: "); Serial.println(tag);
    delay(300); // Debounce e tempo mínimo de movimento
  }
}

void parar() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void executar() {
  digitalWrite(LED_PLAY, HIGH);
  Serial.println("Executando Sequencia...");
  
  for (int i = 0; i < totalComandos; i++) {
    char acao = memoria[i].acao;
    if (acao == 'F') mover(FORWARD, FORWARD, ' ');
    if (acao == 'B') mover(BACKWARD, BACKWARD, ' ');
    if (acao == 'L') mover(BACKWARD, FORWARD, ' ');
    if (acao == 'R') mover(FORWARD, BACKWARD, ' ');
    
    delay(1000); // Cada passo dura 1 segundo na execução
    parar();
    delay(200);
  }
  
  digitalWrite(LED_PLAY, LOW);
  totalComandos = 0; // Limpa a memória após executar
  Serial.println("Fim da Execucao.");
}

void loop() {
  // Alternar Modo Gravação
  if (digitalRead(BTN_REC) == LOW) {
    modoGravacao = !modoGravacao;
    digitalWrite(LED_REC, modoGravacao ? HIGH : LOW);
    if(modoGravacao) totalComandos = 0; // Reset ao iniciar nova gravação
    delay(500);
  }

  // Acionar Execução
  if (digitalRead(BTN_PLAY) == LOW && !modoGravacao) {
    executar();
  }

  // Controle Manual / Gravação
  if (digitalRead(BTN_FRENTE) == LOW) mover(FORWARD, FORWARD, 'F');
  else if (digitalRead(BTN_TRAS) == LOW) mover(BACKWARD, BACKWARD, 'B');
  else if (digitalRead(BTN_ESQ) == LOW) mover(BACKWARD, FORWARD, 'L');
  else if (digitalRead(BTN_DIR) == LOW) mover(FORWARD, BACKWARD, 'R');
  else parar();
}
