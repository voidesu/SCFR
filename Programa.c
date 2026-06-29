/******************************************************************************

Alunos: Amanda Correa e Giovanni Marin
Turma: C11
Data de Início: 15/06/2026

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 

// -------------------------------- STRUCTS --------------------------------    

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
// -------------------------------- VARIAVEIS GLOBAIS --------------------------------    
    
Cliente cliente[20];
int qtdClientes = 0;

Vendas vetorVendas[100];
int qtdVendas = 0;

Parcela vetorParcelas[1000];
int qtdParcelas = 0;
    
// -------------------------------- PROTOTIPO DAS FUNCOES --------------------------------    
    
// Funções de Validação do Cadastro de Clientes
int validarData ( Data dt );
int validarTelefone(char telefone[]);
int validarEmail(char email[]);
int validarCartao(char cartao[]);
int validarCPF(char cpf[]);

// Funções de Clientes
void cadastrarCliente();
void exibirCliente(Cliente c);

// BUSCAR CLIENTES
void buscarPorNome ();
void buscarPorCPF ();
void buscarPorTelefone ();
void menuBuscarCliente ();

// BUSCAR VENDAS
void buscarVendaNome ();
void buscarVendaCPF ();
void buscarVendaTelefone ();
void buscarVendaID ();

// Funções de Registro de Venda e Parcelas
void registroVenda(); // feito
void consultarVendas(); 
int CalcularParcela();
void exibirParcela(Parcela p);
void gerarParcelas(Vendas v); //feito
void exibirVenda(Vendas v);
void exibirParcelasVenda(int idVenda);
    
 
// O MAIN TA AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
void consultarVendas(); //feito
int CalcularParcela();
void gerarParcelas(Vendas v); //feito
void exibirVenda(Vendas v); // feito
void exibirParcelasVenda(int idVenda); //feito
void identificarParcelasVencidas (); // feito
void quitarParcela (); // feito
void liquidarDivida (); // feitoo
 
// -------------------------------- AQUI O MAIN --------------------------------    

int main(){
    int menu = 0;


    // Clientes Fixos para Teste
    strcpy(cliente[0].nome, "Amanda Correa");
    strcpy(cliente[0].CPF, "12135016950");
    strcpy(cliente[0].telefone, "043991231517");
    cliente[0].dataNascimento.dia = 21;
    cliente[0].dataNascimento.mes = 10;
    cliente[0].dataNascimento.ano = 2007;
    strcpy(cliente[0].numeroCartao, "4532015112830366");
    strcpy(cliente[0].chavePix, "amanda@email.com");

    qtdClientes ++;

    strcpy(cliente[1].nome, "Giovanni Marin");
    strcpy(cliente[1].CPF, "52998224725");
    strcpy(cliente[1].telefone, "044991521235");
    cliente[1].dataNascimento.dia = 22;
    cliente[1].dataNascimento.mes = 11;
    cliente[1].dataNascimento.ano = 2008;
    strcpy(cliente[1].numeroCartao, "4556737586899855");
    strcpy(cliente[1].chavePix, "giovanni@email.com");

    qtdClientes ++;


    do {
        printf("\n=============================================================\n");
        printf("                     PAINEL DE COMPRA E VENDAS\n");
        printf("=============================================================\n");
        printf("Desenvolvido por Amanda e Giovanni\n");
        printf("-------------------------------------------------------------\n");
        printf("Escolha uma das opcoes abaixo:\n");
        printf("-------------------------------------------------------------\n");
        printf(" 1 - Cadastrar Cliente\n");
        printf(" 2 - Registrar Venda\n");
        printf(" 3 - Consultar Clientes\n");
        printf(" 4 - Consultar Vendas\n");
        printf(" 5 - Consultar Parcelas\n");
        printf(" 6 - Parcelas Vencidas\n");
        printf(" 7 - Clientes Inadimplentes\n");
        printf(" 8 - Faturamento Total\n");
        printf(" 9 - Valor a Receber\n");
        printf("10 - Valor Recebido\n");
        printf(" 0 - Sair\n");
        printf("-------------------------------------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &menu);
        getchar();
        
        switch(menu) {
            case 1:
                if (qtdClientes < 20) {
					cadastrarCliente();
                } else {
                    printf("\nLimite de clientes atingido!\n");
                }
                break;
                
            case 2:
            	registroVenda();
                break;
                
            case 3:
                menuBuscarCliente();
                break;
                
            case 4:
                consultarVendas();
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

// -------------------------------- FUNÇÕES --------------------------------    

//FUNÇÕES DE VALIDAÇÃO
int validarData ( Data dt ){
    int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((dt.ano % 4 == 0 && dt.ano % 100 != 0) || (dt.ano % 400 == 0)){
		diasMes[2] = 29;
	}

    if (dt.mes >= 1 && dt.mes <= 12) {
        if (dt.dia >= 1 && dt.dia <= diasMes[dt.mes]) {
            if (dt.ano >= 1900) {
                return 1;
            }
        }
    }

    return 0;
}

int validarTelefone (char telefone[]){
    int tamanho = strlen(telefone);
    int i;
    if (telefone[0] == '0') {
        if (tamanho == 11 || tamanho == 12) {
            for(i = 0; i < tamanho; i++){
                if(telefone[i] < '0' || telefone[i] > '9'){
                    return 0;
                }
            }
            return 1;
        }
    }
    return 0;
}

int validarEmail (char email[]) {
    int arroba = 0;
    int posArroba = -1;
    int posPonto = -1;
    int i;
    
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
    int i;
    
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

// funçoes de clientes
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
    while (validarEmail(cliente[qtdClientes].chavePix) == 0){
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

// busca de clientes
void buscarPorNome () {
    int i;
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
    int i;
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
    int i;
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

// buscas pra Vendas
void buscarVendaNome () {
    char nome[50];
    int i;
    int quantidade = 0;
    
    printf("Nome: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome,"\n")] = '\0';
    
    for(i = 0; i<qtdVendas; i++){
        if(strcmp(vetorVendas[i].cliente.nome, nome) == 0) {
            exibirVenda(vetorVendas[i]);
            quantidade++;
        }
    }
    
    if (quantidade == 0) {
        printf("\n Nenhuma venda encontrada!");
    }
}
void buscarVendaCPF () {
    char CPF[50];
    int i;
    int quantidade = 0;
    
    printf("CPF: ");
    fgets(CPF, 50, stdin);
    CPF[strcspn(CPF,"\n")] = '\0';
    
    for(i = 0; i<qtdVendas; i++){
        if(strcmp(vetorVendas[i].cliente.CPF, CPF) == 0) {
            exibirVenda(vetorVendas[i]);
            quantidade++;
        }
    }
    
    if (quantidade == 0) {
        printf("\n Nenhuma venda encontrada!");
    }
}
void buscarVendaTelefone () {
    char telefone[15];
    int i;
    int quantidade = 0;

    printf("Telefone: ");
    fgets(telefone,15,stdin);
    telefone[strcspn(telefone,"\n")] = '\0';

    for(i = 0; i < qtdVendas; i++){

        if(strcmp(vetorVendas[i].cliente.telefone, telefone) == 0){

            exibirVenda(vetorVendas[i]);
            quantidade++;
        }
    }

    if(quantidade == 0){
        printf("\n Nenhuma venda encontrada!");
    }
}
void buscarVendaID (){
    int id;
    int i;

    printf("Digite o ID da venda: ");
    scanf("%d", &id);
    getchar();

    for (i = 0; i < qtdVendas; i++) {
        if (vetorVendas[i].idVenda == id) {
            exibirVenda(vetorVendas[i]);
            return;
        }
    }
    printf("\n Venda nao encontrada!");
}

// funções de  Parcelas e Vendas
void gerarParcelas(Vendas v){

    float valor;
    int i;

    int limite = v.qtdeParcelas;

    if(limite > 10 || limite < 1){
        limite = 10;
    }


    for(i = 1; i <= limite; i++){

        Parcela p;

        p.idParcela = qtdParcelas + 1001;
        p.idVenda = v.idVenda;
        p.numeroDaParcela = i;


        valor = v.valorTotalVenda / limite;
        valor = valor * pow(1.01, i);

        p.valorDaParcela = valor;


        p.dataVencimento = v.dataVenda;

        p.dataVencimento.dia += (30 * i);


    while(p.dataVencimento.dia > 30){

        p.dataVencimento.dia -= 30;
        p.dataVencimento.mes++;

    if(p.dataVencimento.mes > 12){
        p.dataVencimento.mes = 1;
        p.dataVencimento.ano++;
    }
}


        p.dataRecebimento.dia = 0;
        p.dataRecebimento.mes = 0;
        p.dataRecebimento.ano = 0;


        p.situacaoDaParcela = 'A';


        vetorParcelas[qtdParcelas] = p;
        qtdParcelas++;
    }
}

void registroVenda() {
    int idCliente, formaPgto, i;

    if (qtdClientes == 0) {
        printf("\nERRO -> NAO EXISTE NENHUM CLIENTE\n");
        return;
    }

    // MOSTRA LISTA DE CLIENTES
    printf("\n--- CLIENTES CADASTRADOS ---\n");
    for (i = 0; i < qtdClientes; i++) {
        printf("%d - %s (CPF: %s)\n", i, cliente[i].nome, cliente[i].CPF);
    }

    // ESCOLHE O CLIENTE
    printf("\nEscolha o cliente (indice): ");
    scanf("%d", &idCliente);
    getchar();

    if (idCliente < 0 || idCliente >= qtdClientes) {
        printf("\nCliente invalido!\n");
        return;
    }

    // DADOS DA VENDA
    Vendas v;
    v.idVenda = qtdVendas + 1;
    v.cliente = cliente[idCliente];

    printf("Valor total da venda: R$ ");
    scanf("%f", &v.valorTotalVenda);
    getchar();

    printf("Forma de Pagamento:\n");
    printf("1 - Dinheiro\n2 - Pix\n3 - Cartao a Vista\n4 - Cartao Parcelado\n");
    printf("Opcao: ");
    scanf("%d", &formaPgto);
    getchar();

    v.formaPagamento = formaPgto;

    printf("Data da Venda (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &v.dataVenda.dia, &v.dataVenda.mes, &v.dataVenda.ano);
    getchar();

    printf("Observacao: ");
    fgets(v.observacao, 50, stdin);
    v.observacao[strcspn(v.observacao, "\n")] = '\0';

    if (formaPgto == 4) {
        // CARTAO PARCELADO - pergunta quantidade de parcelas (max 10)
        do {
            printf("Quantidade de parcelas (1 a 10): ");
            scanf("%d", &v.qtdeParcelas);
            getchar();
        } while (v.qtdeParcelas < 1 || v.qtdeParcelas > 10);

        vetorVendas[qtdVendas] = v;
        gerarParcelas(v);
    } else {
        // A VISTA - 1 parcela sem juros
        v.qtdeParcelas = 1;

        Parcela p;
        p.idParcela = qtdParcelas + 1001;
        p.idVenda = v.idVenda;
        p.numeroDaParcela = 1;
        p.valorDaParcela = v.valorTotalVenda;

        if (formaPgto == 3) {
            // CARTAO A VISTA - aplicar taxa (ex: 2% de taxa)
            // Regra: Cartao a Vista tem taxa mas nao informaram o valor
            // Se tiver taxa, aplicar aqui: p.valorDaParcela *= 1.02;
        }

        p.dataVencimento = v.dataVenda;
        p.dataRecebimento.dia = 0;
        p.dataRecebimento.mes = 0;
        p.dataRecebimento.ano = 0;
        p.situacaoDaParcela = 'A';

        vetorVendas[qtdVendas] = v;
        vetorParcelas[qtdParcelas] = p;
        qtdParcelas++;
    }

    qtdVendas++;
    printf("\nVenda registrada com sucesso! ID da venda: %d\n", v.idVenda);
}

void consultarVendas() { 
    int opcao;
    
    printf("\n==================================\n");
    printf("         CONSULTAR VENDAS\n");
    printf("==================================\n");
    printf("1 - Buscar por ID da venda\n");
    printf("2 - Buscar por Nome do cliente\n");
    printf("3 - Buscar por CPF do cliente\n");
    printf("4 - Buscar por Telefone do cliente\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    getchar();
    
    switch(opcao){
        case 1:
        buscarVendaID();
        break;
        
        case 2:
        buscarVendaNome ();
        break;
        
        case 3:
        buscarVendaCPF ();
        break;
        
        case 4:
        buscarVendaTelefone();
        break;
        
        default:
        printf("OPCAO INVALIDA!!\n");
        
        case 2:
        buscarVendaNome ();
        break;
        
        case 3:
        buscarVendaCPF ();
        break;
        
        case 4:
        buscarVendaTelefone();
        break;
        
        default:
        printf("OPCAO INVALIDA!!\n");
    }
}

void exibirVenda(Vendas v){

    printf("\n==============================");
    printf("\nID da venda: %d", v.idVenda);
    printf("\nCliente: %s", v.cliente.nome);
    printf("\nCPF: %s", v.cliente.CPF);
    printf("\nValor: R$ %.2f", v.valorTotalVenda);
    printf("\nForma de pagamento: ");
    switch (v.formaPagamento) {
    case 1:
        printf("Dinheiro");
        break;

    case 2:
        printf("Pix");
        break;

    case 3:
        printf("Cartao a Vista");
        break;

    case 4:
        printf("Cartao Parcelado");
        break;
}
    printf("\nParcelas: %d", v.qtdeParcelas);
    printf("\nData: %02d/%02d/%04d", v.dataVenda.dia, v.dataVenda.mes, v.dataVenda.ano);
    printf("\nObservacao: %s\n", v.observacao);
    
    if (v.formaPagamento == 4) {
    exibirParcelasVenda(v.idVenda);
}
}

void exibirParcelasVenda(int idVenda){
    int i;
    
    printf("\n==============================");
    printf("\n         Parcelas\n");
    printf("\n------------------------------");
    
    for(i=0;i<qtdParcelas;i++){
        
        if(vetorParcelas[i].idVenda == idVenda){

            printf("\nParcela %d", vetorParcelas[i].numeroDaParcela);
            printf("\nValor: %.2f", vetorParcelas[i].valorDaParcela);
            printf("\nVencimento: %02d/%02d/%04d",vetorParcelas[i].dataVencimento.dia, vetorParcelas[i].dataVencimento.mes,vetorParcelas[i].dataVencimento.ano);
            printf("\nSituacao: %c\n", vetorParcelas[i].situacaoDaParcela);
        }
    }
}

void identificarParcelasVencidas (){
    int i;
    Data hoje;
    
    printf("Digite a data de hoje (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &hoje.dia, &hoje.mes, &hoje.ano);
    getchar();
    
    for(i=0; i < qtdParcelas; i++) {
        
        if(vetorParcelas[i].situacaoDaParcela == 'A') {
            
            if(vetorParcelas[i].dataVencimento.ano < hoje.ano) {
                vetorParcelas[i].situacaoDaParcela = 'V';
            }
            
            if(vetorParcelas[i].dataVencimento.ano == hoje.ano && 
               vetorParcelas[i].dataVencimento.mes < hoje.mes) {
                   vetorParcelas[i].situacaoDaParcela = 'V';
            }
            
            if(vetorParcelas[i].dataVencimento.ano == hoje.ano && 
               vetorParcelas[i].dataVencimento.mes == hoje.mes &&
               vetorParcelas[i].dataVencimento.dia < hoje.dia) {
                   vetorParcelas[i].situacaoDaParcela = 'V';
            }
         }
    }
    printf ("\n Parcelas vencidas atualizadas!!\n");
}    

void quitarParcela() {
    int idVenda;
    int i;
    Data hoje;
    
    printf("\n==============================");
    printf("\n       Quitar Parcela\n");
    printf("\n------------------------------");
    printf("\n Digite o ID da venda: ");
    scanf("%d", &idVenda);
    getchar();
    
    for (i = 0; i < qtdParcelas; i++ ){
        
        if (vetorParcelas[i].idVenda == idVenda && vetorParcelas[i].situacaoDaParcela == 'A') {
            
            printf("\nDa""ta do pagamento (dd/mm/aaaa): ");
            scanf("%d/%d/%d", &hoje.dia, &hoje.mes, &hoje.ano);
            getchar();
            
            vetorParcelas[i].dataRecebimento = hoje;
            vetorParcelas[i].situacaoDaParcela = 'P';
            
            printf("\n Parcela %d paga com sucesso!! \n", vetorParcelas[i].numeroDaParcela);
            
            return;
        }
        
    }
    
    printf("\nNenhuma parcela pendente encontrada\n");
}

void liquidarDivida () {
    int idVenda;
    int i = 0;
    int quantidade = 0;
    Data hoje;
    
    printf("\n==============================");
    printf("\n       Liquidar Dividas\n");
    printf("\n------------------------------");
    printf("\nDigite o ID da venda: ");
    scanf("%d", &idVenda);
    getchar();
    printf("\nData do pagamento (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &hoje.dia, &hoje.mes, &hoje.ano);
    getchar();
    
    for (i = 0; i < qtdParcelas; i++) {
        if(vetorParcelas[i].idVenda == idVenda && vetorParcelas[i].situacaoDaParcela == 'A') {
            
            vetorParcelas[i].dataRecebimento = hoje;
            vetorParcelas[i].situacaoDaParcela = 'P';
            
            printf("\n Parcela %d quitada!!\n", vetorParcelas[i].numeroDaParcela);
            
            quantidade++;
            
            
        }
    }
    
    if (quantidade == 0) {
        printf("\n Nenhuma Parcela pendente encontrada\n");
    } else {
        printf("\n Divida liquidada!! \n");
    }
    
    
}

void exibirVenda(Vendas v){

    printf("\n==============================");
    printf("\nID da venda: %d", v.idVenda);
    printf("\nCliente: %s", v.cliente.nome);
    printf("\nCPF: %s", v.cliente.CPF);
    printf("\nValor: R$ %.2f", v.valorTotalVenda);
    printf("\nForma de pagamento: ");
    switch (v.formaPagamento) {
    case 1:
        printf("Dinheiro");
        break;

    case 2:
        printf("Pix");
        break;

    case 3:
        printf("Cartao a Vista");
        break;

    case 4:
        printf("Cartao Parcelado");
        break;
}
    printf("\nParcelas: %d", v.qtdeParcelas);
    printf("\nData: %02d/%02d/%04d", v.dataVenda.dia, v.dataVenda.mes, v.dataVenda.ano);
    printf("\nObservacao: %s\n", v.observacao);
    
    if (v.formaPagamento == 4) {
    exibirParcelasVenda(v.idVenda);
}
}

void exibirParcelasVenda(int idVenda){
    int i;
    
    printf("\n==============================");
    printf("\n         Parcelas\n");
    printf("\n------------------------------");
    
    for(i=0;i<qtdParcelas;i++){
        
        if(vetorParcelas[i].idVenda == idVenda){

            printf("\nParcela %d", vetorParcelas[i].numeroDaParcela);
            printf("\nValor: %.2f", vetorParcelas[i].valorDaParcela);
            printf("\nVencimento: %02d/%02d/%04d",vetorParcelas[i].dataVencimento.dia, vetorParcelas[i].dataVencimento.mes,vetorParcelas[i].dataVencimento.ano);
            printf("\nSituacao: %c\n", vetorParcelas[i].situacaoDaParcela);
        }
    }
}
    
    
    
    
