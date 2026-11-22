# Firmware — CyberVault v0.1

## Objetivo

Este diretório documenta o firmware da versão inicial do **CyberVault — Embedded Security Lab**, um protótipo didático de controle de acesso físico com Arduino, teclado matricial, display LCD, servo motor e LEDs.

A versão **v0.1** é uma linha de base intencionalmente vulnerável para estudos de segurança embarcada. **Não deve ser usada para proteger bens ou controlar acesso real.**

## Funcionamento esperado

1. O usuário digita uma senha pelo teclado matricial 4×4.
2. O firmware recebe e processa a entrada.
3. A senha digitada é comparada à senha configurada no programa (no protótipo atual, `1234`).
4. Se a senha for aceita, o sistema aciona o servo para representar a abertura da trava.
5. Se a senha for rejeitada, o acesso não é liberado.
6. O LCD e os LEDs apresentam informações e estados do sistema conforme o código implementado.

> **Nota de verificação:** os textos exatos do LCD, a correspondência de cores dos LEDs, os ângulos do servo, as teclas de confirmação/limpeza e os tempos de espera devem ser conferidos no código `.ino` antes de serem descritos como fatos.

## Documentos

| Arquivo | Finalidade |
| --- | --- |
| [`architecture.md`](architecture.md) | Organização lógica do firmware e responsabilidades dos módulos |
| [`authentication-flow.md`](authentication-flow.md) | Sequência de entrada, validação da senha e acionamento dos componentes |
| [`security-limitations.md`](security-limitations.md) | Limitações conhecidas, hipóteses a validar e plano de mitigação |

## Escopo desta branch

Esta branch contém **somente documentação** da versão v0.1. Não altera o circuito, o comportamento do firmware nem implementa controles de segurança.

## Evidências a adicionar

- [ ] Link para o projeto no Tinkercad.
- [ ] Caminho e versão do código-fonte Arduino (`.ino`).
- [ ] Captura do LCD em espera.
- [ ] Captura ou vídeo de uma tentativa válida.
- [ ] Captura ou vídeo de uma tentativa inválida.
- [ ] Resultado de testes repetidos de senha incorreta, para confirmar a ausência de bloqueio.

## Próxima etapa

Documentar e reproduzir o experimento **CV-01 — Tentativas repetidas de autenticação**, comparar a versão inicial com uma versão protegida e registrar as evidências.
