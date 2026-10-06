# sistema-cadastro-produtos

**Turma:** sala 12A - manhã - grupo 1

## Integrantes
- Ana Clara Rocha Macedo
- Carina Tutihashi
- Rafael Azevedo dos Santos
- Murilo Santos
- Pablo Gonçalves

## Descrição
Sistema em linguagem C, executado no terminal, para controle de produtos de uma loja. Os dados ficam salvos no arquivo `produtos.csv`, com os campos separados por ponto e vírgula (nome, categoria, preço, código e fabricante).

Funcionalidades:
- Cadastrar produto
- Listar produtos
- Buscar por nome
- Buscar por categoria
- Buscar por faixa de preços
- Remover produto
- Atualizar produto

Validações: opção inválida no menu, preço negativo, valores negativos e faixa de preços inválida (mínimo maior que máximo).

## Como compilar e executar
É necessário ter um compilador C instalado (por exemplo, o GCC).

1. Baixe os arquivos `produtos_final.c` e `produtos.csv` e deixe os dois na mesma pasta.
2. Abra o terminal nessa pasta e compile:

        gcc produtos_final.c -o produtos

3. Execute `produtos.exe`.

Também é possível compilar e executar por uma IDE, como Code::Blocks ou Dev-C++.

## Vídeo de apresentação
https://youtu.be/CmHsk4W1Rjw?si=rYPSbsdsERsF8YEv
