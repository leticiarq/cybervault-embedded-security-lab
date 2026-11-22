# Análise de segurança e limitações — firmware v0.1

## Escopo e método

Análise estática do sketch Arduino fornecido. As constatações abaixo são derivadas do código, **não** de um pentest executado nem de medições no hardware físico. O CyberVault é um laboratório didático; a v0.1 não deve ser usada para proteger bens reais.

## SEC-01 — Tentativas ilimitadas de senha

**Evidência no código:** ao pressionar `#`, o firmware compara `senhaDigitada` com `SENHA_CORRETA`, chama `abrirCofre()` ou `negarAcesso()` e limpa a entrada. Não existe contador de falhas nem condição de bloqueio.

**Impacto:** um usuário com acesso ao teclado pode tentar combinações sucessivas. Há um atraso de 2 segundos em cada tentativa incorreta, mas isso não equivale a um limite de tentativas.

**Mitigação planejada:** contador de erros consecutivos, bloqueio temporário após três falhas, política explícita de reinicialização e testes de contorno.

**Experimento:** CV-01 — força bruta / tentativas ilimitadas em ambiente simulado.

## SEC-02 — Senha fixa e embutida no firmware

**Evidência no código:** `const String SENHA_CORRETA = "1234";`.

**Impacto:** a senha é previsível e está exposta a qualquer pessoa que tenha acesso ao código-fonte. O sketch não oferece alteração de senha em tempo de execução.

**Mitigação planejada:** permitir provisionamento/troca controlada de credencial; não distribuir credenciais operacionais no repositório. Em um dispositivo real, a proteção de armazenamento exige avaliação da plataforma.

## SEC-03 — Autenticação baseada em segredo único compartilhado

**Evidência no código:** há uma única variável `SENHA_CORRETA` e a comparação não distingue usuários.

**Impacto:** não há identificação individual, revogação por usuário ou atribuição de ações a uma pessoa específica.

**Mitigação possível:** definir identidades e credenciais distintas se o escopo futuro exigir múltiplos usuários.

## SEC-04 — Ausência de auditoria persistente

**Evidência no código:** `Serial.println("Cofre aberto")`, `Serial.println("Cofre fechado")` e `Serial.println("Senha incorreta")` são as únicas mensagens de resultado. Não há escrita em EEPROM, cartão SD, servidor ou outro armazenamento persistente.

**Impacto:** o sistema não mantém histórico durável de tentativas, horários ou eventos de autenticação.

**Mitigação possível:** projetar registro de eventos com política de retenção, integridade e proteção de dados, respeitando as limitações do microcontrolador.

## SEC-05 — Ausência de sensor de posição ou estado físico

**Evidência no código:** o firmware usa `trava.write(0)` e `trava.write(90)`, mas não consulta sensor que confirme o fechamento ou a abertura física.

**Impacto:** o programa **comanda** a trava, mas não comprova que o mecanismo alcançou a posição esperada. Isso é uma limitação de observabilidade física, não uma exploração demonstrada.

**Mitigação possível:** adicionar sensor de posição/fim de curso e tratamento de falhas mecânicas em versões futuras.

## SEC-06 — Esperas bloqueantes

**Evidência no código:** `delay(5000)` em `abrirCofre()` e `delay(2000)` em `negarAcesso()`.

**Impacto:** durante esses períodos, o `loop()` não processa novas leituras do teclado. Isso limita a responsividade e pode complicar recursos futuros, como alarme, cancelamento ou monitoramento contínuo.

**Mitigação possível:** substituir esperas bloqueantes por controle de estados baseado em `millis()`.

## SEC-07 — Máscara visual não protege o segredo em memória

**Evidência no código:** o LCD imprime `*`, mas `senhaDigitada` contém os caracteres efetivamente pressionados e a senha correta está definida em texto no sketch.

**Impacto:** a máscara protege contra leitura casual da tela, mas não é criptografia nem proteção da credencial no código-fonte.

**Mitigação possível:** adotar um modelo de gestão de credenciais apropriado à capacidade e ao modelo de ameaça do dispositivo.

## O que esta análise NÃO comprova

- Não foi demonstrado ataque remoto: o sketch fornecido não implementa Wi-Fi, Bluetooth ou rede.
- Não foi testada extração de firmware, acesso por interfaces de depuração ou adulteração física.
- Não foi medida a taxa real de tentativas nem o comportamento do servo em hardware físico.
- Não foi atribuída pontuação CVSS: isso exige contexto e modelo de ameaça definidos; a ausência de uma pontuação não significa ausência de risco.

## Plano de evolução

| Versão/experimento | Objetivo | Critério de aceitação sugerido |
| --- | --- | --- |
| v0.1 — baseline | Preservar comportamento vulnerável | Testes AUTH-01 a AUTH-08 reproduzidos |
| CV-01 — exploração | Demonstrar tentativas incorretas sucessivas | Evidência de ausência de bloqueio |
| CV-01 — correção | Limitar falhas consecutivas | Após 3 erros, negar novas tentativas por 30 s |
| CV-01 — regressão | Confirmar que a proteção não quebra o fluxo legítimo | Acesso correto, limpeza, expiração e reinício testados |

> O comportamento diante de reinicialização durante um bloqueio deverá ser definido na implementação segura. Um contador apenas em RAM pode ser zerado por reset.

## Referência

Constatações baseadas exclusivamente no código-fonte Arduino do CyberVault MVP v0.1 fornecido para a documentação.
