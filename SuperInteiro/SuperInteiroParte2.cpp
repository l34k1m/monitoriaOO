#include <iostream>

#define TAM_VETOR 40

using namespace std;

class Inteirao {
	private:
	int valor[TAM_VETOR];

	public:
	Inteirao();
	Inteirao(string);
	Inteirao(int *);
	~Inteirao();
	int * getValor();
	void setValor(string);
	void setValor(int *);
	void operator = (Inteirao);
	Inteirao operator * (Inteirao);
	unsigned long long int operator / (Inteirao);
	Inteirao operator % (Inteirao);
};

	Inteirao::Inteirao() {
	}

	Inteirao::Inteirao(string entrada) {
		setValor(entrada);
	}

	Inteirao::Inteirao(int * entrada) {
		setValor(entrada);
	}

	Inteirao::~Inteirao() {
	}

	int * Inteirao::getValor() {
		return valor;
	}

	void Inteirao::setValor(string entrada) {
		int i;
		for (i=0; i<TAM_VETOR; i++) {
			valor[i] = 0;
		}
		int tamanhoEntrada = entrada.length();
		int excedenteArray = TAM_VETOR-tamanhoEntrada;
		for (i=tamanhoEntrada-1; i>=0; i--) {
			valor[excedenteArray+i] = entrada.at(i) - 48;
		}
	}

	void Inteirao::setValor(int * entrada) {
		int i;
		for (i=0;i<TAM_VETOR;i++) {
			this->valor[i] = *(entrada+i);
		}
	}

	void Inteirao::operator = (Inteirao inteiroB) {
		int *pNumeroB;
		pNumeroB = inteiroB.getValor();
		this->setValor(pNumeroB);
	}
	
	Inteirao Inteirao::operator * (Inteirao inteiroB) {
		int numeroA[TAM_VETOR], numeroB[TAM_VETOR];
		int resultado[TAM_VETOR];
		int *pNumeroA, *pNumeroB;
		int passoDeslocamento = 0;
		int i = 0;
		int j = 0; //a ideia e fazer uma multiplicação usando cada um dos 
		int resultadoOperacaoAtual = 0;
		int excesso = 0;

		for (i=0; i<TAM_VETOR; i++) {
			numeroA[i] = 0;
			numeroB[i] = 0;
			resultado[i] = 0;
		}

		pNumeroA = this->getValor();
		pNumeroB = inteiroB.getValor();

		for (i=0;i<TAM_VETOR;i++) {
			numeroA[i] = *(pNumeroA+i);
			numeroB[i] = *(pNumeroB+i);
		}
		
		for (i=TAM_VETOR-1; i>=0; i--) {	//laco para selecionar um numero debaixo por vez e fazer a rodada de multiplicacao
			if (numeroB[i] != 0) {
				for (j=TAM_VETOR-1; j>=0; j--) {	//para atualizar todo uma rodada de multiplicacao
					resultado[j-passoDeslocamento] += numeroA[j] * numeroB[i];
					if (resultado[j-passoDeslocamento] >=10) {
						resultado[j-passoDeslocamento-1] += resultado[j-passoDeslocamento] / 10;
						resultado[j-passoDeslocamento] %= 10;
					}
				}
				passoDeslocamento++;	//ajusta o deslocamento necessario para cada rodada da multiplicacao
			} else {
				passoDeslocamento++;
			}
		}
	
	Inteirao multiplicacao = Inteirao(resultado);
	return multiplicacao;
		
	}
	
	unsigned long long int Inteirao::operator / (Inteirao inteiroB) {
		int numeroA[TAM_VETOR], numeroB[TAM_VETOR];
		int *pNumeroA, *pNumeroB;
		int i = 0;
		int j = 0;	//usada na subtracao implicita
		int k = 0;	//usada na subtracao implicita
		unsigned long int quociente = 0;
		bool divisivel = true;
		bool emprestar = true;
		
		int resultadoOperacaoAtual = 0;
		int excesso = 0;

		for (i=0; i<TAM_VETOR; i++) {
			numeroA[i] = 0;
			numeroB[i] = 0;
		}

		pNumeroA = this->getValor();
		pNumeroB = inteiroB.getValor();

		for (i=0;i<TAM_VETOR;i++) {
			numeroA[i] = *(pNumeroA+i);
			numeroB[i] = *(pNumeroB+i);
			//cout << numeroA[i];
		}
		
		//cout << endl;

		while(divisivel) {
			for (i=0;i<TAM_VETOR;i++) {	//quando o B for menor ou igual ao que sobrar de A, hora de parar
				if (numeroA[i] > numeroB[i]) {
					//divisivel = true;
					//cout << "A maior que B";
					break;
				} 
				if (numeroA[i] < numeroB[i]) {
					//cout << "numeroA menor que numeroB" << endl;
					divisivel = false;
					break;
				}
			}
			//cout << "Fim do laco for" << endl;
			
			if (divisivel) {
				for (i=TAM_VETOR-1; i>=0; i--) {
					if (numeroA[i] >= numeroB[i]) {
						resultadoOperacaoAtual = numeroA[i] - numeroB[i];
						numeroA[i] = resultadoOperacaoAtual;
					}	else {
						j = i;
						j--;
						emprestar = true;
						while (emprestar) {
							if (numeroA[j] > 0) {
								numeroA[j]--;
								for (int k=j+1; k<i; k++) {
									numeroA[k]+=10;
									numeroA[k]--;
								}
								numeroA[i] += 10;
								emprestar = false;
							} else {
								j--;
							}
						}
						i++;
					}
				}
				quociente++;	//numero de vezes que deu para subtrair numeroB de numeroA
			}
		}
		return quociente;
	}
	
	Inteirao Inteirao::operator % (Inteirao inteiroB) {
		int numeroA[TAM_VETOR], numeroB[TAM_VETOR];
		int resultado[TAM_VETOR];
		int *pNumeroA, *pNumeroB;
		int i = 0;
		int j = 0;	//usada na subtracao implicita
		int k = 0;	//usada na subtracao implicita
		unsigned long int quociente = 0;
		bool divisivel = true;
		bool emprestar = true;
		
		int resultadoOperacaoAtual = 0;

		for (i=0; i<TAM_VETOR; i++) {
			numeroA[i] = 0;
			numeroB[i] = 0;
			resultado[i] = 0;
		}

		pNumeroA = this->getValor();
		pNumeroB = inteiroB.getValor();

		for (i=0;i<TAM_VETOR;i++) {
			numeroA[i] = *(pNumeroA+i);
			numeroB[i] = *(pNumeroB+i);
			//cout << numeroA[i];
		}
		
		//cout << endl;

		while(divisivel) {
			for (i=0;i<TAM_VETOR;i++) {	//quando o B for menor ou igual ao que sobrar de A, hora de parar
				if (numeroA[i] > numeroB[i]) {
					//divisivel = true;
					//cout << "A maior que B";
					break;
				} 
				if (numeroA[i] < numeroB[i]) {
					//cout << "numeroA menor que numeroB" << endl;
					divisivel = false;
					break;
				}
			}
			//cout << "Fim do laco for" << endl;
			
			if (divisivel) {
				for (i=TAM_VETOR-1; i>=0; i--) {
					if (numeroA[i] >= numeroB[i]) {
						resultadoOperacaoAtual = numeroA[i] - numeroB[i];
						numeroA[i] = resultadoOperacaoAtual;
					}	else {
						j = i;
						j--;
						emprestar = true;
						while (emprestar) {
							if (numeroA[j] > 0) {
								numeroA[j]--;
								for (int k=j+1; k<i; k++) {
									numeroA[k]+=10;
									numeroA[k]--;
								}
								numeroA[i] += 10;
								emprestar = false;
							} else {
								j--;
							}
						}
						i++;
					}
				}
			}
		}
		Inteirao resto = Inteirao(numeroA);
		return resto;
	}

int main() {
	string entrada;
	int inteiraoMultiplicacao[TAM_VETOR], inteiraoDivisao[TAM_VETOR], inteiraoResto[TAM_VETOR], inteiraoAtribuicao[TAM_VETOR];
	int *pMultiplicacao, *pDivisao, *pResto, *pAtribuicao;
	int i;
	unsigned long int divisao;
	Inteirao multiplicacao, resto, atribuicao;

	for (i=0; i<TAM_VETOR; i++) {
		inteiraoMultiplicacao[i] = 0;
		inteiraoDivisao[i] = 0;
		inteiraoAtribuicao[i] = 0;
	}

	cin >> entrada;
	Inteirao inteiroA = Inteirao(entrada);

	cin >> entrada;
	Inteirao inteiroB = Inteirao(entrada);
	
	multiplicacao = inteiroA * inteiroB;	//momento em que o a sobrecarga para simbolo * entra em acao
	pMultiplicacao = multiplicacao.getValor();
	for (i=0;i<TAM_VETOR;i++) {
		inteiraoMultiplicacao[i] = *(pMultiplicacao+i);
		cout << inteiraoMultiplicacao[i];
	}
	cout << endl;

	divisao = inteiroA / inteiroB;	//momento em que o a sobrecarga para simbolo / entra em acao
	cout << divisao << endl;
	
	resto = inteiroA % inteiroB;
	pResto = resto.getValor();
	for (i=0;i<TAM_VETOR;i++) {
		inteiraoResto[i] = *(pResto+i);
		cout << inteiraoResto[i];
	}
	cout << endl;
	/*
	inteiroA = inteiroB;	//realizando o uso de operador de atribuicao entre os objetos, possivel por sobrecarga
	pAtribuicao = inteiroA.getValor();
	for (i=0;i<TAM_VETOR;i++) {
		inteiraoAtribuicao[i] = *(pAtribuicao+i);
		cout << inteiraoAtribuicao[i];
	}
	*/
	
	//cout << endl;

	pMultiplicacao = NULL;
	delete pMultiplicacao;
	pDivisao = NULL;
	delete pDivisao;
	pAtribuicao = NULL;
	delete pAtribuicao;
}

