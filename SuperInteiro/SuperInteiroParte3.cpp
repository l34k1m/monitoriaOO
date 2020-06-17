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
	void operator ++ (int);
	void operator -- (int);
	void operator += (Inteirao);
	void operator -= (Inteirao);
	void operator *= (Inteirao);
	void operator /= (Inteirao);
};

	Inteirao::Inteirao() {
		int i;
		for (i=0; i<TAM_VETOR; i++) {
			valor[i] = 0;
		}
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
	
	void Inteirao::operator ++ (int) {
		int numeroA[TAM_VETOR], numeroIncremento[TAM_VETOR];
		int resultado[TAM_VETOR];
		int *pNumeroA;
		int i = 0;
		int resultadoOperacaoAtual = 0;
		int excesso = 0;

		for (i=0; i<TAM_VETOR; i++) {
			numeroA[i] = 0;
			numeroIncremento[i] = 0;
			resultado[i] = 0;
		}

		pNumeroA = this->getValor();

		for (i=0;i<TAM_VETOR;i++) {
			numeroA[i] = *(pNumeroA+i);
		}

		numeroIncremento[TAM_VETOR-1] = 1;
		
		for (i=TAM_VETOR-1; i>=0; i--) {
				resultadoOperacaoAtual = numeroA[i] + numeroIncremento[i] + excesso;
			excesso = 0;
			if (resultadoOperacaoAtual > 9) {
				excesso = 1;
				resultadoOperacaoAtual %= 10;
			}
			resultado[i] = resultadoOperacaoAtual;
		}

		this->setValor(resultado);
		
		pNumeroA = NULL;
		delete pNumeroA;
	}

	void Inteirao::operator -- (int) {
		int numeroA[TAM_VETOR], numeroB[TAM_VETOR];
		int resultado[TAM_VETOR];
		int *pNumeroA;
		int i = 0;
		int j = 0;
		int k = 0;
		bool emprestar = true;
		int resultadoOperacaoAtual = 0;

		for (i=0; i<TAM_VETOR; i++) {
			numeroA[i] = 0;
			numeroB[i] = 0;
			resultado[i] = 0;
		}

		pNumeroA = this->getValor();

		for (i=0;i<TAM_VETOR;i++) {
			numeroA[i] = *(pNumeroA+i);
		}
		
		numeroB[TAM_VETOR-1] = 1;

		for (i=TAM_VETOR-1; i>=0; i--) {
			if (numeroA[i] >= numeroB[i]) {
				resultadoOperacaoAtual = numeroA[i] - numeroB[i];
				resultado[i] = resultadoOperacaoAtual;
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
		
		this->setValor(resultado);
		
		pNumeroA = NULL;
		delete pNumeroA;
	}
	
	void Inteirao::operator += (Inteirao inteiroB) {
		int numeroA[TAM_VETOR], numeroB[TAM_VETOR];
		int resultado[TAM_VETOR];
		int *pNumeroA, *pNumeroB;
		int i = 0;
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

		for (i=TAM_VETOR-1; i>=0; i--) {
			resultadoOperacaoAtual = numeroA[i] + numeroB[i] + excesso;
			excesso = 0;
			if (resultadoOperacaoAtual > 9) {
				excesso = 1;
				resultadoOperacaoAtual %= 10;
			}
			resultado[i] = resultadoOperacaoAtual;
		}

		this->setValor(resultado);
		
		pNumeroA = NULL;
		delete pNumeroA;
		pNumeroB = NULL;
		delete pNumeroB;
	}

	void Inteirao::operator -= (Inteirao inteiroB) {
		int numeroA[TAM_VETOR], numeroB[TAM_VETOR];	//trabalhar diretamente com ponteiros aqui seria muito ruim
		int resultado[TAM_VETOR];
		int *pNumeroA, *pNumeroB;
		int i = 0;
		int j = 0;	//para saber a posicao do numero B a ser subtraido de A
		int k = 0;	//variavel para contar reajuste de vizinhos vazios no "caminho de volta" do emprestimo
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
		}

		for (i=TAM_VETOR-1; i>=0; i--) {
			if (numeroA[i] >= numeroB[i]) {
				resultadoOperacaoAtual = numeroA[i] - numeroB[i];
				resultado[i] = resultadoOperacaoAtual;
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

		this->setValor(resultado);
		
		pNumeroA = NULL;
		delete pNumeroA;
		pNumeroB = NULL;
		delete pNumeroB;
	}
	
	void Inteirao::operator *= (Inteirao inteiroB) {
		int numeroA[TAM_VETOR], numeroB[TAM_VETOR];
		int resultado[TAM_VETOR];
		int *pNumeroA, *pNumeroB;
		int passoDeslocamento = 0;
		int i = 0;
		int j = 0;
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

		for (i=TAM_VETOR-1; i>=0; i--) {
			if (numeroB[i] != 0) {
				for (j=TAM_VETOR-1; j>=0; j--) {
					resultado[j-passoDeslocamento] += numeroA[j] * numeroB[i];
					if (resultado[j-passoDeslocamento] >=10) {
						resultado[j-passoDeslocamento-1] += resultado[j-passoDeslocamento] / 10;
						resultado[j-passoDeslocamento] %= 10;
					}
				}
				passoDeslocamento++;
			} else {
				passoDeslocamento++;
			}
		}
		this->setValor(resultado);
		
		pNumeroA = NULL;
		delete pNumeroA;
		pNumeroB = NULL;
		delete pNumeroB;
	}
	
	void Inteirao::operator /= (Inteirao inteiroB) {
		int numeroA[TAM_VETOR], numeroB[TAM_VETOR];
		Inteirao resultado;
		int *pNumeroA, *pNumeroB;
		int i = 0;
		int j = 0;	//usada na subtracao implicita
		int k = 0;	//usada na subtracao implicita
		bool divisivel = false;
		bool emprestar = true;
		//unsigned long int quociente = 0;


		int resultadoOperacaoAtual = 0;

		for (i=0; i<TAM_VETOR; i++) {
			numeroA[i] = 0;
			numeroB[i] = 0;
		}

		pNumeroA = this->getValor();
		pNumeroB = inteiroB.getValor();

		for (i=0;i<TAM_VETOR;i++) {
			numeroA[i] = *(pNumeroA+i);
			numeroB[i] = *(pNumeroB+i);
		}

		for (i=0;i<TAM_VETOR;i++) {	//evitar divisao por zero
			if (numeroB[i] != 0) {
				divisivel = true;
			}
		}

		while(divisivel) {
			for (i=0;i<TAM_VETOR;i++) {	//quando o B for menor ou igual ao que sobrar de A, hora de parar
				if (numeroA[i] < numeroB[i]) {
					divisivel = false;
					break;
				}
				if (numeroA[i] > numeroB[i]) {
					break;
				}
			}
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
				//quociente++;
				resultado++;
			}
		}
		this->setValor(resultado.getValor());
		
		pNumeroA = NULL;
		delete pNumeroA;
		pNumeroB = NULL;
		delete pNumeroB;
	}
	
	int main() {
	string entrada;
	
	int inteiraoIncremento[TAM_VETOR];
	int inteiraoDecremento[TAM_VETOR];
	int inteiraoSomaAtribuicao[TAM_VETOR];
	int inteiraoSubtracaoAtribuicao[TAM_VETOR];
	int inteiraoMultiplicacaoAtribuicao[TAM_VETOR];
	int inteiraoDivisaoAtribuicao[TAM_VETOR];
	
	int *pIncremento;
	int *pDecremento;
	int *pSomaAtribuicao;
	int *pSubtracaoAtribuicao;
	int *pMultiplicacaoAtribuicao;
	int *pDivisaoAtribuicao;
	
	int i;

	for (i=0; i<TAM_VETOR; i++) {
		inteiraoIncremento[i] = 0;
		inteiraoDecremento[i] = 0;
		inteiraoSomaAtribuicao[i] = 0;
		inteiraoSubtracaoAtribuicao[i] = 0;
		inteiraoMultiplicacaoAtribuicao[i] = 0;
		inteiraoDivisaoAtribuicao[i] = 0;
	}

	cin >> entrada;
	Inteirao inteiroA = Inteirao(entrada);

	cin >> entrada;
	Inteirao inteiroB = Inteirao(entrada);

	inteiroA++;
	pIncremento = inteiroA.getValor();
	for (i=0;i<TAM_VETOR;i++) {
		inteiraoIncremento[i] = *(pIncremento+i);
		cout << inteiraoIncremento[i];
	}
	cout << endl;
	
	inteiroA--;
	pDecremento = inteiroA.getValor();
	for (i=0;i<TAM_VETOR;i++) {
		inteiraoDecremento[i] = *(pDecremento+i);
		cout << inteiraoDecremento[i];
	}
	cout << endl;
	
	inteiroA += inteiroB;
	pSomaAtribuicao = inteiroA.getValor();
	for (i=0;i<TAM_VETOR;i++) {
		inteiraoSomaAtribuicao[i] = *(pSomaAtribuicao+i);
		cout << inteiraoSomaAtribuicao[i];
	}
	cout << endl;
	
	inteiroA -= inteiroB;
	pSubtracaoAtribuicao = inteiroA.getValor();
	for (i=0;i<TAM_VETOR;i++) {
		inteiraoSubtracaoAtribuicao[i] = *(pSubtracaoAtribuicao+i);
		cout << inteiraoSubtracaoAtribuicao[i];
	}
	cout << endl;
	
	inteiroA *= inteiroB;
	pMultiplicacaoAtribuicao = inteiroA.getValor();
	for (i=0;i<TAM_VETOR;i++) {
		inteiraoMultiplicacaoAtribuicao[i] = *(pMultiplicacaoAtribuicao+i);
		cout << inteiraoMultiplicacaoAtribuicao[i];
	}
	cout << endl;
	
	inteiroA /= inteiroB;
	pDivisaoAtribuicao = inteiroA.getValor();
	for (i=0;i<TAM_VETOR;i++) {
		inteiraoDivisaoAtribuicao[i] = *(pDivisaoAtribuicao+i);
		cout << inteiraoDivisaoAtribuicao[i];
	}
	cout << endl;
	
	pIncremento = NULL;
	delete pIncremento;
	pDecremento = NULL;
	delete pDecremento;
	pSomaAtribuicao = NULL;
	delete pSomaAtribuicao;
	pSubtracaoAtribuicao = NULL;
	delete pSubtracaoAtribuicao;
	pMultiplicacaoAtribuicao = NULL;
	delete pMultiplicacaoAtribuicao;
	pDivisaoAtribuicao = NULL;
	delete pDivisaoAtribuicao;
}
