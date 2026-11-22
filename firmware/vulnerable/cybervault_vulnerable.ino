#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// LCD
LiquidCrystal lcd(10, 11, A0, A1, A2, A3);

// Teclado 4x4
const byte LINHAS = 4;
const byte COLUNAS = 4;

char teclas[LINHAS][COLUNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinosLinhas[LINHAS] = {2, 3, 4, 5};
byte pinosColunas[COLUNAS] = {6, 7, 8, 9};

Keypad teclado = Keypad(
  makeKeymap(teclas),
  pinosLinhas,
  pinosColunas,
  LINHAS,
  COLUNAS
);

// Servo e LEDs
Servo trava;

const int PINO_SERVO = 12;
const int LED_VERDE = A4;
const int LED_VERMELHO = A5;

// Autenticacao
const String SENHA_CORRETA = "1234";
String senhaDigitada = "";

void mostrarTelaInicial() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CYBERVAULT");
  lcd.setCursor(0, 1);
  lcd.print("Senha: ");
}

void fecharCofre() {
  trava.write(0);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  Serial.println("Cofre fechado");
}

void abrirCofre() {
  lcd.clear();
  lcd.print("ACESSO PERMITIDO");

  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);

  trava.write(90);

  Serial.println("Cofre aberto");

  delay(5000);

  fecharCofre();
}

void negarAcesso() {
  lcd.clear();
  lcd.print("ACESSO NEGADO");

  digitalWrite(LED_VERMELHO, HIGH);
  digitalWrite(LED_VERDE, LOW);

  Serial.println("Senha incorreta");

  delay(2000);

  digitalWrite(LED_VERMELHO, LOW);
}

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  trava.attach(PINO_SERVO);

  fecharCofre();
  mostrarTelaInicial();
}

void loop() {
  char tecla = teclado.getKey();

  if (tecla == NO_KEY) {
    return;
  }

  // Digitar senha
  if (tecla >= '0' && tecla <= '9') {
    if (senhaDigitada.length() < 4) {
      senhaDigitada += tecla;

      lcd.setCursor(
        7 + senhaDigitada.length() - 1, 1
      );

      lcd.print("*");
    }
  }

  // Apagar senha
  if (tecla == '*') {
    senhaDigitada = "";
    mostrarTelaInicial();
  }

  // Confirmar senha
  if (tecla == '#') {
    if (senhaDigitada == SENHA_CORRETA) {
      abrirCofre();
    } else {
      negarAcesso();
    }

    senhaDigitada = "";
    mostrarTelaInicial();
  }
}
