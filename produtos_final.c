#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "produtos.csv"

typedef struct {
    char nome[100];
    char categoria[50];
    float preco;
    char codigo_prod[15];
    char fabricante[50];
   } Produto;

void cadastrar() {
    Produto p;
    FILE *f = fopen(ARQUIVO, "a");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    
    printf("Digite o nome do produto: ");
    scanf(" %99[^\n]", p.nome);
    printf("Digite a categoria do produto: ");
    scanf(" %49[^\n]", p.categoria);
    do {
    printf("Digite o preço do produto: ");
    scanf("%f", &p.preco);
    if (p.preco < 0) {
        printf("O preço não pode ser negativo.\n");
    }
}  while (p.preco < 0);
    printf("Digite o código do produto: ");
    scanf(" %14[^\n]", p.codigo_prod  );
    printf("Digite o fabricante do produto: ");
    scanf(" %49[^\n]", p.fabricante  );
    

    fprintf(f, "%s;%s;%.2f;%s;%s\n", p.nome, p.categoria, p.preco, p.codigo_prod, p.fabricante);
    fclose(f);
    printf("Produto salvo com sucesso!\n");
}

void listar() {
    Produto c;
    int total = 0;
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("A lista de produtos está vazia.\n");
        return;
    }

    printf("\n--- PRODUTOS ---\n");
    char linha[250];

    //fgets() lê uma linha do arquivo f e armazena em linha
    while (fgets(linha, 250, f) != NULL) {

	    strcpy(c.nome, strtok(linha, ";\n"));     //strtok() procura o primeiro ; e pega tudo que está antes dele. 
	    strcpy(c.categoria, strtok(NULL, ";\n"));
	    c.preco = atof(strtok(NULL, ";\n"));  //aqui o strtok pega na mesma string no proximo trecho . O NULL permite isso
	    strcpy(c.codigo_prod, strtok(NULL, ";\n"));
	    strcpy(c.fabricante, strtok(NULL, ";\n"));

        printf("\nNome: %s\n", c.nome);
        printf("Categoria: %s\n", c.categoria);
        printf("Preço do Produto: %.2f\n", c.preco);
        printf("Código do produto: %s\n", c.codigo_prod);
        printf("Fabricante do produto: %s\n", c.fabricante);
    }
    fclose(f);
}

void buscarNome() {
	
    FILE *f = fopen(ARQUIVO, "r");
    Produto c;
    char linha[250];
    char nomeBusca[100];
    int encontrou = 0;

    if (f == NULL) {
        printf("Arquivo vazio.\n");
        return;
    }

    printf("Digite o nome do produto: ");
    scanf(" %99[^\n]", nomeBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {

        strcpy(c.nome, strtok(linha, ";\n"));
        strcpy(c.categoria, strtok(NULL, ";\n"));
        c.preco = atof(strtok(NULL, ";\n"));
        strcpy(c.codigo_prod, strtok(NULL, ";\n"));
        strcpy(c.fabricante, strtok(NULL, ";\n"));

        if (strcmp(c.nome, nomeBusca) == 0) {

            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", c.nome);
            printf("Categoria: %s\n", c.categoria);
            printf("Preco: %.2f\n", c.preco);
            printf("Codigo: %s\n", c.codigo_prod);
            printf("Fabricante: %s\n", c.fabricante);

            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Produto nao encontrado.\n");

    fclose(f);
}


void buscarCategoria() {

    FILE *f = fopen(ARQUIVO, "r");
    Produto c;
    char linha[250];
    char categoriaBusca[50];
    int encontrou = 0;

    if (f == NULL) {
        printf("Arquivo vazio.\n");
        return;
    }

    printf("Digite a categoria: ");
    scanf(" %49[^\n]", categoriaBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {

        strcpy(c.nome, strtok(linha, ";\n"));
        strcpy(c.categoria, strtok(NULL, ";\n"));
        c.preco = atof(strtok(NULL, ";\n"));
        strcpy(c.codigo_prod, strtok(NULL, ";\n"));
        strcpy(c.fabricante, strtok(NULL, ";\n"));

        if (strcmp(c.categoria, categoriaBusca) == 0) {

            printf("\nNome: %s\n", c.nome);
            printf("Preco: %.2f\n", c.preco);

            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum produto encontrado.\n");

    fclose(f);
}

void buscarFaixaPreco() {

    FILE *f = fopen(ARQUIVO, "r");
    Produto c;
    char linha[250];
    float minimo, maximo;
    int encontrou = 0;

    if (f == NULL) {
        printf("Arquivo vazio.\n");
        return;
    }

    printf("Digite o preco minimo: ");
    scanf("%f", &minimo);

    printf("Digite o preco maximo: ");
    scanf("%f", &maximo);

    if (minimo < 0 || maximo < 0) {
    printf("Os valores nao podem ser negativos.\n");
    fclose(f);
    return;
}
if (minimo > maximo) {
    printf("O preco minimo nao pode ser maior que o maximo.\n");
    fclose(f);
    return;
  }   
    while (fgets(linha, sizeof(linha), f) != NULL) {

        strcpy(c.nome, strtok(linha, ";\n"));
        strcpy(c.categoria, strtok(NULL, ";\n"));
        c.preco = atof(strtok(NULL, ";\n"));
        strcpy(c.codigo_prod, strtok(NULL, ";\n"));
        strcpy(c.fabricante, strtok(NULL, ";\n"));

        if (c.preco >= minimo && c.preco <= maximo) {

            printf("\nNome: %s\n", c.nome);
            printf("Preco: %.2f\n", c.preco);

            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum produto encontrado nessa faixa.\n");

    fclose(f);
}



void remover() {
    FILE *f = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.txt", "w");

    char linha[250];
    char nomeBusca[100];
    Produto c;
    int encontrou = 0;

    if (f == NULL) {
        printf("A lista de produtos está vazia.\n");
        return;
    }

    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(f);
        return;
    }

    printf("Digite o nome do produto que deseja remover: ");
    scanf(" %99[^\n]", nomeBusca);

    while (fgets(linha, 250, f) != NULL) {

        char copia[250];
        strcpy(copia, linha);

        strcpy(c.nome, strtok(copia, ";\n"));
        strcpy(c.categoria, strtok(NULL, ";\n"));
        c.preco = atof(strtok(NULL, ";\n"));
        strcpy(c.codigo_prod, strtok(NULL, ";\n"));
        strcpy(c.fabricante, strtok(NULL, ";\n"));

        if (strcmp(c.nome, nomeBusca) == 0) {
            encontrou = 1;
        }
        else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.txt", ARQUIVO);

    if (encontrou == 1) {
        printf("Produto removido com sucesso!\n");
    }
    else {
        printf("Produto nao encontrado.\n");
    }
}

void atualizar() {
    FILE *f = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.txt", "w");

    char linha[250];
    char nomeBusca[100];
    Produto c;
    int encontrou = 0;

    if (f == NULL) {
        printf("A lista de produtos est� vazia.\n");
        return;
    }

    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(f);
        return;
    }

    printf("Digite o nome do produto que deseja atualizar: ");
    scanf(" %99[^\n]", nomeBusca);

    while (fgets(linha, 250, f) != NULL) {

        char copia[250];
        strcpy(copia, linha);

        strcpy(c.nome, strtok(copia, ";\n"));
        strcpy(c.categoria, strtok(NULL, ";\n"));
        do {
    printf("Digite o novo preço: ");
    scanf(" %f", &c.preco);
    if (c.preco < 0) printf("O preço não pode ser negativo.\n");
} while (c.preco < 0);
        strcpy(c.codigo_prod, strtok(NULL, ";\n"));
        strcpy(c.fabricante, strtok(NULL, ";\n"));

        if (strcmp(c.nome, nomeBusca) == 0) {

            encontrou = 1;

            printf("Digite o novo nome: ");
            scanf(" %99[^\n]", c.nome);

            printf("Digite a nova categoria: ");
            scanf(" %49[^\n]", c.categoria);

            printf("Digite o novo preço: ");
            scanf(" %f", &c.preco);

            printf("Digite o novo código: ");
            scanf(" %14[^\n]", c.codigo_prod);

            printf("Digite o novo fabricante: ");
            scanf(" %49[^\n]", c.fabricante);

            fprintf(temp, "%s;%s;%.2f;%s;%s\n",
                    c.nome,
                    c.categoria,
                    c.preco,
                    c.codigo_prod,
                    c.fabricante);
        }
        else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.txt", ARQUIVO);

    if (encontrou == 1) {
        printf("Produto atualizado com sucesso!\n");
    }
    else {
        printf("Produto nao encontrado.\n");
    }
}

int main(){
	setlocale(LC_ALL,"portuguese");
	
	int op;
	
	do{
		printf("\n=====================================");
		printf("\n       CONTROLE DE PRODUTOS          ");
		printf("\n=====================================");
		printf("\n1 - Cadastrar produto");
		printf("\n2 - Listar produtos");
		printf("\n3 - Buscar produtos por nome");
		printf("\n4 - Buscar produtos por categoria");
		printf("\n5 - Buscar produtos por faixa de preços");
		printf("\n6 - Remover produto");
		printf("\n7 - Atualizar produto"); 
		printf("\n0 - Sair");
		printf("\nEntre com a opção desejada: ");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				printf("Cadastrar novo produto\n");
				cadastrar();
				break;
			case 2:
				printf("Listar um produto\n");
				listar();
				break;
			case 3:
				printf("Buscar produto por nome\n");
				buscarNome();
				break;
			case 4: 
				printf("Buscar produto por categoria\n");
				buscarCategoria();
				break;
			case 5: 
				printf("Buscar produtos por faixa de preço\n");
				buscarFaixaPreco();
				break;
			case 6:
				printf("Remover produto\n");
				remover();
				break;
			case 7:
				printf("Atualizar produto\n");
				atualizar();
				break;
			case 0:
				printf("Encerrando programa....\n");
				break;
			default:
				printf("Opção Invalida!\n");
			       
		}
		
	}
	while(op != 0);
	return 0;
}
