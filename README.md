# Projeto: Shell 238P
📖 Descrição

Este projeto foi desenvolvido na disciplina Projeto e Implementação de Sistemas Operacionais, onde o objetivo do laboratório era criar um shell simples em linguagem C, semelhante aos terminais Unix.

O shell implementa os conceitos fundamentais de gerenciamento de processos, chamadas de sistema e entrada/saída (I/O), utilizando funções como fork(), execvp(), waitpid(), dup2() e open().

⚙️ Funcionalidades Implementadas

✅ Execução de programas externos

238p$ ls


✅ Redirecionamento de entrada e saída

238p$ echo "teste" > saida.txt
238p$ cat < saida.txt


✅ Comandos internos

cd — muda o diretório atual

history — exibe os últimos comandos digitados

exit — encerra o shell

✅ Histórico de comandos
Armazena até 100 comandos digitados durante a sessão atual.

🧪 Testes Automatizados

Um script de testes (test_sh238p.sh) foi criado para validar todas as funcionalidades do shell.

Resultado da execução:

[OK] Teste 1: comando ls executado com sucesso
[OK] Teste 2: echo com argumento
[OK] Teste 3: redirecionamento de saída >
[OK] Teste 4: redirecionamento de entrada <
[OK] Teste 5: comando interno cd executado
[OK] Teste 6: comando history funcionando
[OK] Teste 7: comando exit encerra shell

🧩 Estrutura do Projeto
.
├── sh238p.c           # Código-fonte principal
├── Makefile           # Automação de compilação e criação do zip
├── teste.sh     # Script de testes automatizados
└── README.md          # Documentação do projeto

🛠️ Compilação e Execução

Compilar o shell:

make


Executar o shell:

./sh238p


Rodar os testes automatizados:

./test_sh238p.sh


Gerar o arquivo ZIP para submissão:

make zip

📚 Conceitos Envolvidos

Criação e gerenciamento de processos (fork, waitpid)

Execução de programas (execvp)

Redirecionamento de descritores (dup2, open, close)

Manipulação de entrada padrão (getline)

Estruturas de dados simples para histórico de comandos

Tratamento de erros e alocação dinâmica de memória




👨‍💻 Autor

Elivelton Moura
Estudante de Engenharia da Computação – UFC Quixadá
Apaixonado por sistemas operacionais, programação de baixo nível e desenvolvimento embarcado.