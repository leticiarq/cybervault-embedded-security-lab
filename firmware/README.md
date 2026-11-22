# CyberVault — Firmware MVP v0.1

## Objetivo

Este diretório documenta o firmware original do CyberVault MVP v0.1, um protótipo didático de cofre controlado por senha com Arduino Uno, teclado matricial 4×4, LCD 16×2, servomotor e LEDs. A implementação descrita é **vulnerável por projeto** e será preservada como referência para experimentos de segurança posteriores.

## Bibliotecas

- `Keypad.h`: leitura das teclas do teclado matricial.
- `LiquidCrystal.h`: controle do LCD em modo paralelo.
- `Servo.h`: controle do servomotor que representa a trava.

## Hardware controlado pelo firmware

| Dispositivo | Pinos usados no código | Papel |
| --- | --- | --- |
| Teclado 4×4 | Linhas: D2–D5; colunas: D6–D9 | Entrada de senha e comandos |
| LCD 16×2 | `LiquidCrystal(10, 11, A0, A1, A2, A3)` | Exibe mensagens e mascara dígitos |
| Servomotor | D12 | Simula abertura e fechamento |
| LED verde | A4 | Indica acesso permitido |
| LED vermelho | A5 | Indica acesso negado |
| Serial | 9600 baud | Emite mensagens de estado |

> Os pinos listados são os declarados no firmware. A conferência física das ligações deve ser feita com a documentação do hardware.

## Uso do protótipo

1. Inicialize a simulação e aguarde a tela `CYBERVAULT` / `Senha:`.
2. Digite de um a quatro números. Cada número aceito aparece como `*` no LCD.
3. Pressione `#` para comparar a entrada com a senha fixa `1234`.
4. Pressione `*` para limpar a entrada atual e retornar à tela inicial.
5. As teclas `A`, `B`, `C` e `D` não possuem ações implementadas.

### Resultado da confirmação

- **Senha correta:** mostra `ACESSO PERMITIDO`, acende LED verde, posiciona o servo em 90°, espera 5 segundos, retorna o servo a 0° e apaga os LEDs.
- **Senha incorreta:** mostra `ACESSO NEGADO`, acende LED vermelho por 2 segundos e o apaga; o servo não é comandado para abrir.
- Após qualquer confirmação, o firmware limpa a senha digitada e restaura a tela inicial.

## Organização da documentação

- [`architecture.md`](architecture.md): constantes, variáveis, objetos, funções e execução do firmware.
- [`authentication-flow.md`](authentication-flow.md): fluxograma e casos de teste da autenticação.
- [`security-limitations.md`](security-limitations.md): análise de riscos e limitações observáveis no código.

## Escopo

Esta documentação descreve o código fornecido para a **v0.1**. Não implementa melhorias de segurança nem afirma que o protótipo foi validado em hardware físico. O primeiro experimento previsto é o **CV-01 — tentativas ilimitadas de senha**.
