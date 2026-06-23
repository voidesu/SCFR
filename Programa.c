/******************************************************************************

Alunos: Amanda Correa e Giovanni Marin
Turma: C11
Data de Início: 15/06/2026

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 

// STRUCTS

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Cliente {
    char nome[50];
    char CPF[50];
    char telefone[15];
    Data dataNascimento;
    char numeroCartao[20];
    char chavePix[30];
} Cliente;

typedef struct Vendas {
    Cliente cliente;
    int idVenda;
    float valorTotalVenda;
    int formaPagamento;
    int qtdeParcelas;
    Data dataVenda;
    char observacao[50];
} Vendas; 

typedef struct Parcela {
    int idParcela;
    int idVenda;
    int numeroDaParcela;
    float valorDaParcela;
    Data dataVencimento;
    Data dataRecebimento;
    char situacaoDaParcela;
} Parcela;

// VARIAVEIS GLOBAIS

int i = 0, j = 0, soma = 0; 
    
Cliente cliente[50];
int qtdClientes = 0;


Vendas vetorVendas[100];
int qtdVendas = 0;
Parcela vetorParcelas[1000];
int qtdParcelas = 0;
    
// PROTOTIPO DAS FUNCOES     
    
// Funções de Validação do Cadastro de Clientes
int validarData ( Data dt );
int validarTelefone(char telefone[]);
int validarEmail(char email[]);
int validarCartao(char cartao[]);
int validarCPF(char cpf[]);

// Funções de Clientes
void cadastrarCliente();
void exibirCliente(Cliente c);

// BUSCA DE CLIENTES
void buscarPorNome ();
void buscarPorCPF ();
void buscarPorTelefone ();
void menuBuscarCliente ();

// Funções de Registro de Venda e Parcelas
//int registroVenda(); 
int CalcularParcela();
void exibirParcela(Parcela p);
void gerarParcelas(Vendas v);
  

int main(){
    int menu = 0;

    do {
        printf("\n=============================================================\n");
        printf("                     PAINEL DE COMPRA E VENDAS\n");
        printf("=============================================================\n");
        printf("Desenvolvido por Amanda e Giovanni\n");
        printf("-------------------------------------------------------------\n");
        printf("Escolha uma das opcoes abaixo:\n");
        printf("-------------------------------------------------------------\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Registrar Venda\n");
        printf("3 - Consultar Clientes\n");
        printf("4 - Consultar Parcelas\n");
        printf("5 - Parcelas Vencidas\n");
        printf("6 - Clientes Inadimplentes\n");
        printf("7 - Faturamento Total\n");
        printf("8 - Valor a Receber\n");
        printf("9 - Valor Recebido\n");
        printf("0 - Sair\n");
        printf("-------------------------------------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &menu);
        getchar();
        
        switch(menu) {
            case 1:
                if (qtdClientes < 50) {
					cadastrarCliente();
                } else {
                    printf("\nLimite de clientes atingido!\n");
                }
                break;
            case 2:
            	//registroVenda();
                break;
                
            case 3:
                menuBuscarCliente();
                break;
                
            case 4:
                break;
                
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
                
            default:
                printf("\nOpcao Invalida!\n");
                break;
        }
    } while (menu != 0);

    return 0;
}

int validarData ( Data dt ){
    int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((dt.ano % 4 == 0 && dt.ano % 100 != 0) || (dt.ano % 400 == 0)){
		diasMes[2] = 29;
	}
    if (dt.dia >= 1 && dt.dia <= diasMes[dt.mes]){
        if (dt.mes>=1 && dt.mes<=12) {
            if (dt.ano >= 1900) {
                return 1;
            }
        }
    }
    return 0;
}

int validarTelefone (char telefone[]) {
    int tamanho = strlen(telefone);
    int i = 0;
    
    if (telefone[0] != '0' ) { 
        return 0;
    }
    
    if (tamanho != 11 && tamanho != 12) {
        return 0;
    }
        
    for(i = 0; i < tamanho; i++){
		if(telefone[i] < '0' || telefone[i] > '9'){
			return 0;
		}
	}
    return 1;
}
int validarEmail (char email[]) {
    int arroba = 0;
    int posArroba = -1;
    int posPonto = -1;
    
    for ( i = 0; i < strlen(email); i++) {
        if( email[i] == '@' ) {
            arroba++;
            posArroba = i;
        }
        
        if ( email[i] == '.' ) {
            posPonto = i;
        }
    }
    
    if ( arroba != 1) { return 0; }
    if ( posArroba < 2) { return 0; }
    if ( posPonto == -1) { return 0; }
    if ( posPonto - posArroba - 1 < 2) { return 0; }
    if ( strlen(email) - posPonto - 1 < 2) { return 0; }

    return 1;
}

int validarCartao (char cartao[]){
    int tamanho = strlen(cartao);
    int numero = 0;
    int somaLocal = 0; 
    int dobrar = 0;
    
    for(i = tamanho - 1; i>=0; i--){
        numero = cartao[i] - '0';
        
        if (dobrar == 1) { 
            numero = numero * 2;
            if (numero > 9) {
                numero = numero - 9;
            }
        }
        
        somaLocal = somaLocal + numero;
     
        if (dobrar == 0) { 
            dobrar = 1;
        } else {
            dobrar = 0;
        }
    }
    
    if (somaLocal % 10 == 0) {
        return 1;
    }
    else {
        return 0; 
    }
}

int validarCPF(char cpf[]) {
    char cpfLimpo[12]; 
    int k, indiceLimpo = 0;
    int somaLocal = 0, resto = 0;
    int primeiroDigito = 0, segundoDigito = 0;

    // LIMPA O CPF SEM OS '-' e '.'
    for (k = 0; cpf[k] != '\0'; k++) {
        if (cpf[k] >= '0' && cpf[k] <= '9') {
            if (indiceLimpo < 11) { 
                cpfLimpo[indiceLimpo] = cpf[k];
                indiceLimpo++;
            } else {
                return 0; 
            }
        }
    }
    cpfLimpo[indiceLimpo] = '\0'; 


    if (indiceLimpo != 11) {
        return 0;
    }


    // PRIMEIRO DIGITO VERIFICADOR
    somaLocal = 0;
    int peso = 10;
    for (k = 0; k < 9; k++) {
        somaLocal += (cpfLimpo[k] - '0') * peso;
        peso--;
    }
    
    resto = (somaLocal * 10) % 11;
    if (resto == 10 || resto == 11) {
        primeiroDigito = 0;
    } else {
        primeiroDigito = resto;
    }

    // SEGUNDO DIGITO VERIFICADOR
    somaLocal = 0;
    peso = 11;
    for (k = 0; k < 10; k++) {
        somaLocal += (cpfLimpo[k] - '0') * peso;
        peso--;
    }
    
    resto = (somaLocal * 10) % 11;
    if (resto == 10 || resto == 11) {
        segundoDigito = 0;
    } else {
        segundoDigito = resto;
    }

    if ((cpfLimpo[9] - '0' == primeiroDigito) && (cpfLimpo[10] - '0' == segundoDigito)) {
        return 1; // CPF Válido!
    } else {
        return 0; // CPF Inválido!
    }
}

void cadastrarCliente() {
    // REGISTRA O NOME
    printf("\nNome..: ");
    fgets(cliente[qtdClientes].nome, 50, stdin);
    cliente[qtdClientes].nome[strcspn(cliente[qtdClientes].nome, "\n")] = '\0';
	// CPF
    printf("CPF..: ");
    fgets(cliente[qtdClientes].CPF, 50, stdin);
    cliente[qtdClientes].CPF[strcspn(cliente[qtdClientes].CPF, "\n")] = '\0';
	// LOOPA A FUNCAO DE VALIDAR CPF, NAO EH POSSIVEL CRIAR UM CPF INVALIDO
    while (validarCPF(cliente[qtdClientes].CPF) == 0) {
        printf("CPF INVALIDO! Tente novamente..: ");
        fgets(cliente[qtdClientes].CPF, 50, stdin);
        cliente[qtdClientes].CPF[strcspn(cliente[qtdClientes].CPF, "\n")] = '\0';
    }
	// TELEFONE
    printf("Telefone..: ");
    fgets(cliente[qtdClientes].telefone, 15, stdin);
    cliente[qtdClientes].telefone[strcspn(cliente[qtdClientes].telefone, "\n")] = '\0';
	// LOOPA A FUNCAO DE VALIDAR TELEFONE, NAO EH POSSIVEL CRIAR UM TELEFONE INVALIDO
    while (validarTelefone(cliente[qtdClientes].telefone) == 0) {
        printf("TELEFONE INVALIDO! Tente novamente..: ");
        fgets(cliente[qtdClientes].telefone, 15, stdin);
        cliente[qtdClientes].telefone[strcspn(cliente[qtdClientes].telefone, "\n")] = '\0';
    }
	// VERIFICA A DATA
    printf("Data de Nascimento (dd/mm/aaaa)..: ");
    scanf("%d/%d/%d", &cliente[qtdClientes].dataNascimento.dia, &cliente[qtdClientes].dataNascimento.mes, &cliente[qtdClientes].dataNascimento.ano);
    getchar();
	// LOOPA A FUNCAO DE VALIDAR DATA, NAO EH POSSIVEL CRIAR UM DATA INVALIDA
    while (validarData(cliente[qtdClientes].dataNascimento) == 0) {
        printf("DATA INVALIDA! Tente novamente..: ");
        scanf("%d/%d/%d", &cliente[qtdClientes].dataNascimento.dia, 
                          &cliente[qtdClientes].dataNascimento.mes, 
                          &cliente[qtdClientes].dataNascimento.ano);
        getchar();
    }
	// CARTAO
    printf("Numero do Cartao...: ");
    fgets(cliente[qtdClientes].numeroCartao, 20, stdin);
    cliente[qtdClientes].numeroCartao[strcspn(cliente[qtdClientes].numeroCartao, "\n")] = '\0';
	// LOOPA A FUNCAO DE VALIDAR CARTAO, NAO EH POSSIVEL CRIAR UM CARTAO INVALIDO
    while (validarCartao(cliente[qtdClientes].numeroCartao) == 0) {
        printf("NUMERO DO CARTAO INVALIDO! Tente novamente..: ");
        fgets(cliente[qtdClientes].numeroCartao, 20, stdin);
        cliente[qtdClientes].numeroCartao[strcspn(cliente[qtdClientes].numeroCartao, "\n")] = '\0';
    }
	// PIX
    printf("Chave Pix...: ");
    fgets(cliente[qtdClientes].chavePix, 30, stdin);
    cliente[qtdClientes].chavePix[strcspn(cliente[qtdClientes].chavePix, "\n")] = '\0';
	//LOOPA A FUNCAO DE VALIDAR PIX, NAO EH POSSIVEL CRIAR UM PIX INVALIDO
    while (validarCartao(cliente[qtdClientes].numeroCartao) == 0){
        printf("CHAVE PIX INVALIDA! Tente novamente..: ");
        fgets(cliente[qtdClientes].chavePix, 30, stdin);
        cliente[qtdClientes].chavePix[strcspn(cliente[qtdClientes].chavePix, "\n")] = '\0';
    }
    
    qtdClientes++; 
    
    printf("\n Cadastro Completo!!\n");
}

void exibirCliente(Cliente c) {
    printf("\nNome: %s", c.nome);
    printf("\nCPF: %s", c.CPF);
    printf("\nTelefone: %s", c.telefone);
    printf("\nData de Nascimento: %02d/%02d/%04d", c.dataNascimento.dia, c.dataNascimento.mes, c.dataNascimento.ano);
    printf("\nCartao: %s", c.numeroCartao);
    printf("\nChave Pix: %s", c.chavePix);
}

void buscarPorNome () {
    char nome[50];
    printf("Digite o nome..: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    for (i = 0; i < qtdClientes; i++) {
        if (strcmp(cliente[i].nome, nome) == 0) {
            exibirCliente(cliente[i]);
            return;
        }
    }
    printf("\nCliente nao encontrado!\n");
}

void buscarPorCPF () {
    char CPF[50];
    printf("Digite o CPF..: ");
    fgets(CPF, 50, stdin);
    CPF[strcspn(CPF, "\n")] = '\0';
    
    for ( i = 0; i < qtdClientes; i++) {
        if (strcmp(cliente[i].CPF, CPF) == 0) {
            exibirCliente(cliente[i]);
            return;
        }
    }
    printf("\nCliente nao encontrado!\n");
}

void buscarPorTelefone () {
    char telefone[15];
    printf("Digite o telefone..: ");
    fgets(telefone, 15, stdin);
    telefone[strcspn(telefone, "\n")] = '\0'; 
    
    for (i = 0; i < qtdClientes; i++) {
        if (strcmp(cliente[i].telefone, telefone) == 0) {
            exibirCliente(cliente[i]);
            return;
        }
    }
    printf("\nCliente nao encontrado!\n");
}

void menuBuscarCliente () {
    int menu = 0;
    printf("=============================================================\n");
    printf("                        BUSCA DE CLIENTES\n");
    printf("=============================================================\n");
    printf("Escolha uma das opcoes abaixo:\n");
    printf("-------------------------------------------------------------\n");
    printf("1 - Buscar cliente por Nome\n");
    printf("2 - Buscar cliente por CPF\n");
    printf("3 - Buscar cliente por Telefone\n");
    printf("-------------------------------------------------------------\n");
    printf("Opcao: ");
    scanf("%d",&menu);
    getchar();
    
    switch(menu) {
        case 1: buscarPorNome(); break;
        case 2: buscarPorCPF(); break;
        case 3: buscarPorTelefone(); break;
        default: printf("Opcao Invalida!\n");
    }
}

void gerarParcelas(Vendas v){
    float valor;
    for(i=1;i<=v.qtdeParcelas;i++){
        Parcela p;
        p.idParcela=qtdParcelas+1001;
        p.idVenda=v.idVenda;
        p.numeroDaParcela=i;
        
        // JUROS
        valor=(v.valorTotalVenda/v.qtdeParcelas);
        valor = valor * pow(1.01,i);
        // CRIACAO
        p.valorDaParcela=valor;
        p.dataVencimento=v.dataVenda;
        p.dataVencimento.mes += i;
        // + 12 meses = Passa para o proximo ano
        if(p.dataVencimento.mes>12){
            p.dataVencimento.mes-=12;
            p.dataVencimento.ano++;
        }
        
        p.dataRecebimento.dia=0;
        p.dataRecebimento.mes=0;
        p.dataRecebimento.ano=0;
        
        p.situacaoDaParcela='A';
        
		vetorParcelas[qtdParcelas] = p;
        
		qtdParcelas++;
    }
}
