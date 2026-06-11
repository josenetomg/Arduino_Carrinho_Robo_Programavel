# ArduinoUno-MemoryRobot 🤖

Este projeto implementa um robô programável utilizando Arduino Uno e o Motor Shield L293D.

O robô possui dois modos: manual/gravação e execução autônoma.

## 🚀 Funcionalidades
- **Modo Manual:** Controle direto pelos botões direcionais.
- **Modo Programação (REC):** Armazena a sequência de botões pressionados em um buffer de memória.
- **Modo Execução (PLAY):** Reproduz a rota gravada de forma sequencial.
- **Sinalização Visual:** LEDs indicam se o sistema está em modo de gravação ou executando uma tarefa.

## 🔌 Pinagem Utilizada
- **Motores:** Saídas M1 e M2 do L293D Shield.
- **Botões Direcionais:** A0 a A3 (configurados como Input Pull-up).
- **Controle de Sistema:** Pino 2 (REC) e Pino 13 (PLAY).
- **Feedback Visual:** A4 (LED REC) e A5 (LED PLAY).

## 🛠️ Como usar
1. Monte o shield sobre o Arduino Uno.
2. Conecte os motores e os botões conforme o mapeamento.
3. Ligue o Arduino e pressione o botão **REC** (O LED REC acenderá).
4. Pressione as direções para criar o caminho.
5. Pressione **REC** novamente para finalizar.
6. Pressione **PLAY** para ver o robô repetir os movimentos.

## 📦 Dependências
- Biblioteca `AFMotor.h` (Adafruit Motor Shield library).
