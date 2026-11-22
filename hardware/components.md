# Componentes eletrônicos — CyberVault v0.1

## Objetivo

Explicar **o que é**, **como funciona**, **para que serve no CyberVault** e **quais cuidados de ligação** cada componente da montagem simulada exige. Esta descrição corresponde à captura [circuit-overview.png](../assets/screenshots/circuit-overview.png).

## 1. Arduino Uno R3 (1 unidade)

**O que é:** placa de desenvolvimento baseada no microcontrolador ATmega328P.

**Como funciona:** executa o firmware gravado em sua memória e lê/aciona sinais em pinos digitais e analógicos. O `setup()` é executado na inicialização e o `loop()` repete a lógica do sistema. O Arduino fornece linhas de alimentação de 5 V e GND para os componentes da simulação.

**No CyberVault:** recebe a tecla pressionada, valida a senha, mostra mensagens no LCD, aciona o servo e controla os LEDs. Os pinos D0 e D1 permanecem livres para comunicação serial com o computador.

**Cuidados:** os pinos de entrada/saída não são fontes de potência para motores. No protótipo simulado, o servo usa a alimentação de 5 V; numa montagem real pode precisar de fonte própria com terra comum.

## 2. Protoboard (1 unidade)

**O que é:** placa para interligar componentes sem solda.

**Como funciona:** os furos de cada grupo de cinco na região central normalmente são eletricamente conectados entre si. Barramentos identificados por `+` e `−` permitem distribuir alimentação; alguns são interrompidos no meio.

**No CyberVault:** distribui 5 V/GND e fornece pontos de conexão para LEDs, resistores e potenciômetro.

**Cuidados:** dois terminais colocados na mesma faixa conectada equivalem a um único nó elétrico. Verifique as divisões dos barramentos.

## 3. Teclado matricial 4×4 (1 unidade)

**O que é:** conjunto de 16 teclas organizado em quatro linhas e quatro colunas.

**Como funciona:** pressionar uma tecla fecha o contato entre uma linha e uma coluna. O firmware varre as linhas e consulta as colunas para descobrir a tecla pressionada, geralmente com auxílio da biblioteca `Keypad`.

**No CyberVault:** permite digitar os quatro dígitos da senha; `#` confirma e `*` limpa a entrada na implementação atual.

**Ligações lógicas:** linhas R1–R4 → D2–D5; colunas C1–C4 → D6–D9. A posição física dos oito terminais deve ser conferida no simulador.

## 4. LCD 16×2 (1 unidade)

**O que é:** display de caracteres com duas linhas de 16 posições.

**Como funciona:** recebe sinais de controle (`RS`, `E`) e dados. O modo de **4 bits** usa somente `D4` a `D7`, economizando pinos do Arduino. `RW` em GND mantém o display em escrita. A iluminação de fundo usa `LED+` e `LED−`.

**No CyberVault:** exibe nome do sistema, campo de senha e mensagens como acesso permitido/negado.

**Ligações:** `RS` → D10, `E` → D11; `D4…D7` → A0…A3; alimentação/contraste/iluminação detalhados em [wiring.md](wiring.md).

## 5. Potenciômetro de 10 kΩ (1 unidade)

**O que é:** resistor variável de três terminais.

**Como funciona:** entre os terminais externos forma uma resistência total; o terminal central (cursor) fornece uma tensão intermediária ajustável.

**No CyberVault:** regula a tensão de contraste no pino `VO` do LCD para tornar os caracteres visíveis.

**Ligações:** externos → 5 V e GND; central → LCD `VO`. Trocar os externos apenas inverte o sentido de ajuste.

## 6. Micro servo (1 unidade)

**O que é:** atuador com controle de posição angular.

**Como funciona:** recebe alimentação, GND e um sinal de controle de pulsos. A biblioteca `Servo` permite solicitar posições angulares. A posição real depende da faixa e do modelo do servo.

**No CyberVault:** simula o mecanismo de travamento: 0° representa fechado e 90° representa aberto.

**Ligações:** alimentação → 5 V; terra → GND; sinal → D12. Verifique o nome dos terminais no Tinkercad; as cores dos fios podem variar.

## 7. LED verde (1 unidade)

**O que é:** diodo emissor de luz.

**Como funciona:** conduz corrente predominantemente em um sentido e emite luz quando polarizado diretamente. Deve ter limitação de corrente.

**No CyberVault:** sinaliza a autenticação bem-sucedida enquanto o cofre está aberto.

**Ligações:** A4 → resistor de 220 Ω → ânodo (+); cátodo (−) → GND.

## 8. LED vermelho (1 unidade)

**O que é / como funciona:** mesmo princípio do LED verde.

**No CyberVault:** sinaliza uma tentativa de acesso negada.

**Ligações:** A5 → resistor de 220 Ω → ânodo (+); cátodo (−) → GND.

## 9. Resistores de 220 Ω (3 unidades na configuração documentada)

**O que são:** componentes passivos que oferecem resistência à passagem de corrente.

**Como funcionam:** limitam a corrente conforme a diferença de tensão e a resistência (Lei de Ohm, `I = V/R`). Não possuem polaridade.

**No CyberVault:** um resistor em série com cada LED de indicação e um resistor em série com o positivo da iluminação de fundo do LCD. A necessidade e o valor exato do resistor de backlight dependem do módulo LCD; aqui seguimos a montagem simulada.

**Cuidados:** a resistência deve ficar **em série**, não com as duas pontas no mesmo nó elétrico da protoboard.

## 10. Fios de ligação (jumpers)

**O que são:** condutores elétricos que estabelecem conexões entre pinos e furos da protoboard.

**No CyberVault:** interligam teclado e LCD diretamente ao Arduino e levam energia/sinais aos demais componentes. Cores são apenas convenções de organização: vermelho (5 V), preto (GND) e outras cores para sinais.

## Resumo

| Componente | Quantidade | Responsabilidade principal |
|---|---:|---|
| Arduino Uno R3 | 1 | Executar a lógica do cofre |
| Protoboard | 1 | Distribuir alimentação e conexões |
| Teclado matricial 4×4 | 1 | Entrada da senha |
| LCD 16×2 | 1 | Exibir o estado do sistema |
| Potenciômetro 10 kΩ | 1 | Ajustar o contraste |
| Micro servo | 1 | Simular a trava |
| LED verde | 1 | Indicar acesso permitido |
| LED vermelho | 1 | Indicar acesso negado |
| Resistores 220 Ω | 3 | Limitar corrente de LEDs/backlight |
| Jumpers | Conforme montagem | Conexões elétricas |

> **Limite do protótipo:** o CyberVault v0.1 é uma simulação didática de controle de acesso. Não substitui uma fechadura física certificada e ainda não implementa as proteções de segurança propostas para os desafios futuros.
