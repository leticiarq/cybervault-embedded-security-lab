# Limitações de segurança — CyberVault v0.1

## Propósito

Identificar riscos da implementação inicial e organizar hipóteses para experimentos controlados no Tinkercad. O objetivo é comparar a versão vulnerável com melhorias posteriores, sem apresentar hipóteses como vulnerabilidades já comprovadas.

## Limitações e hipóteses

| ID | Item | Situação | Risco potencial | Verificação recomendada |
| --- | --- | --- | --- | --- |
| CV-01 | Ausência de limite de tentativas | Hipótese a confirmar | Adivinhação repetida de senhas | Executar sucessivas entradas inválidas e observar bloqueios |
| CV-02 | Senha curta e previsível (`1234`) | Configuração conhecida do protótipo | Baixa resistência à adivinhação | Confirmar a senha no código e testar alternativas |
| CV-03 | Senha armazenada diretamente no firmware | A verificar no `.ino` | Exposição do segredo em código ou binário | Inspecionar definição e uso da senha |
| CV-04 | Ausência de registro de tentativas | A verificar | Dificuldade de auditoria | Inspecionar logs, Serial e persistência |
| CV-05 | Ausência de persistência de bloqueio | A verificar | Reinício pode apagar estado de segurança | Verificar comportamento após reset |

## CV-01 — Tentativas ilimitadas de senha

### Descrição

Se o sistema aceitar novas tentativas imediatamente após uma falha, sem impor limite ou atraso, um usuário com acesso físico ao teclado poderá testar múltiplas combinações.

### Pré-condições

- Acesso ao teclado do protótipo ou ao simulador.
- Sistema operacional e pronto para receber entradas.

### Procedimento de validação

1. Iniciar a simulação.
2. Digitar uma senha incorreta.
3. Registrar a resposta do LCD, LEDs e servo.
4. Repetir o processo pelo menos cinco vezes.
5. Verificar se existe bloqueio ou espera obrigatória.
6. Registrar capturas e resultados na documentação do experimento.

### Impacto

Possibilidade de tentativas repetidas de adivinhação de senha, caso a hipótese seja confirmada. A probabilidade de sucesso depende do tamanho, da previsibilidade da senha e das condições de acesso ao dispositivo.

### Mitigação planejada

- Limitar tentativas consecutivas (proposta inicial: três falhas).
- Aplicar bloqueio temporário (proposta inicial: 30 segundos).
- Informar o bloqueio ao usuário pelo LCD.
- Definir claramente quando o contador de falhas é reiniciado.
- Testar o comportamento após reinicialização do dispositivo.

> **Atenção:** um bloqueio apenas em memória pode ser contornado por reinicialização. Essa limitação deve ser discutida e testada na versão protegida.

## CV-02 — Senha previsível

A senha `1234` é adequada para demonstração didática, mas inadequada para um controle de acesso real. Recomenda-se avaliar senhas menos previsíveis e uma política de autenticação apropriada ao hardware.

## Critérios para considerar uma vulnerabilidade confirmada

- Comportamento reproduzido no simulador.
- Versão do firmware identificada.
- Passos documentados.
- Evidências capturadas.
- Impacto descrito sem exagero.
- Correção e teste de regressão registrados separadamente.

## Fora do escopo desta branch

Esta documentação não implementa correções, não altera a senha, não modifica o circuito e não comprova automaticamente as hipóteses listadas. As alterações serão desenvolvidas em branches próprias.
