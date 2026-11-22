# Hardware — CyberVault v0.1

Esta pasta documenta a **montagem física simulada** do CyberVault no Tinkercad Circuits. O circuito representa um cofre eletrônico com entrada por teclado, exibição no LCD, indicação luminosa e trava acionada por micro servo.

## Navegação

- [Componentes](components.md) — função, princípio de funcionamento e papel de cada peça.
- [Conexões](wiring.md) — mapa de pinos do Arduino, LCD e teclado; alimentação e cuidados.
- [Montagem e verificação](assembly.md) — sequência reproduzível para montar e testar o circuito.
- [Captura do circuito](../assets/screenshots/circuit-overview.png) — imagem da montagem atual no Tinkercad.

## Escopo desta versão

Documenta o hardware **presente na captura da v0.1**: Arduino Uno, teclado 4×4, LCD 16×2, protoboard, potenciômetro, micro servo, LEDs verde e vermelho, resistores e fios. **Não há buzzer na imagem**, portanto ele não faz parte da montagem documentada aqui.

O programa Arduino, a lógica de autenticação e os testes de software serão detalhados depois, na branch `docs/firmware`.

> Nota de reprodução: a captura é uma referência visual. Confirme os nomes dos terminais no Tinkercad antes de fazer uma ligação, especialmente no teclado e no servo.
