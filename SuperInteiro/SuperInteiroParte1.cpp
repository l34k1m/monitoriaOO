#include <iostream>

#define TAM_VETOR 40

using namespace std;

class Inteirao {
	private:
	int valor[TAM_VETOR];

	public:
	Inteirao();
	Inteirao(string entrada);
	Inteirao(int * entrada);
	~Inteirao();
	int * getValor();
	void setValor(string entrada);
	void setValor(int * entrada);
	string operator == (Inteirao);
	string operator != (Inteirao);
	Inteirao operator + (Inteirao);
	Inteirao operator - (Inteirao);
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

	string Inteirao::operator == (Inteirao inteiroB) {
		int numeroA[TAM_VETOR], numeroB[TAM_VETOR];	//eu poderia ter trabalhado diretamente com ponteiros, mas seria ruim em algumas operacoes
		int *pNumeroA, *pNumeroB;
		int i = 0, diferenca = 0;
		string resultado;

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
		i = 0;
		while (diferenca == 0 && i<40) {
			if (numeroA[i] != numeroB[i]) {
				diferenca++;
			}
			i++;
		} if (diferenca == 0) {
			resultado = "iguais";	//vai aparecer se der igual
		}

		pNumeroA = NULL;
		delete pNumeroA;
		pNumeroB = NULL;
		delete pNumeroB;

		return resultado;
	}

	string Inteirao::operator != (Inteirao inteiroB) {
		int numeroA[TAM_VETOR], numeroB[TAM_VETOR];
		int *pNumeroA, *pNumeroB;
		int i = 0, diferenca = 0;
		string resultado;

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
		i = 0;
		while (diferenca == 0 && i<TAM_VETOR) {
			if (numeroA[i] != numeroB[i]) {
				diferenca++;
			}
			i++;
		} if (diferenca != 0) {
			resultado = "diferentes";	//vai aparecer se der diferente
		}

		pNumeroA = NULL;
		delete pNumeroA;
		pNumeroB = NULL;
		delete pNumeroB;

		return resultado;
	}

	Inteirao Inteirao::operator + (Inteirao inteiroB) {
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

		pNumeroA = NULL;
		delete pNumeroA;
		pNumeroB = NULL;
		delete pNumeroB;

		Inteirao soma = Inteirao(resultado);
		return soma;
	}

	Inteirao Inteirao::operator - (Inteirao inteiroB) {
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

		pNumeroA = NULL;
		delete pNumeroA;
		pNumeroB = NULL;
		delete pNumeroB;

		Inteirao subtracao = Inteirao(resultado);
		return subtracao;
	}

int main() {
	string entrada;
	int *pSoma, *pSubtracao;
	int i;
	string igualdade = "", diferenca = "";
	int inteiraoSoma[TAM_VETOR], inteiraoSubtracao[TAM_VETOR];
	Inteirao soma, subtracao;

	for (i=0; i<TAM_VETOR; i++) {
		inteiraoSoma[i] = 0;
		inteiraoSubtracao[i] = 0;
	}

	cin >> entrada;
	Inteirao inteiroA = Inteirao(entrada);

	cin >> entrada;
	Inteirao inteiroB = Inteirao(entrada);

	igualdade = inteiroA == inteiroB;
	if (igualdade != "") {
		cout << igualdade << endl;	//colocado num laco para evitar o pulo de linha com valor vazio
	}

	diferenca = inteiroA != inteiroB;
	if (diferenca != "") {
		cout << diferenca << endl;	//colocado num laco para evitar o pulo de linha com valor vazio
	}

	soma = inteiroA + inteiroB;
	pSoma = soma.getValor();
	for (i=0;i<TAM_VETOR;i++) {
		inteiraoSoma[i] = *(pSoma+i);
		cout << inteiraoSoma[i];
	}
	cout << endl;

	subtracao = inteiroA - inteiroB;
	pSubtracao = subtracao.getValor();
	for (i=0;i<TAM_VETOR;i++) {
		inteiraoSubtracao[i] = *(pSubtracao+i);
		cout << inteiraoSubtracao[i];
	}

	pSoma = NULL;
	delete pSoma;
	pSubtracao = NULL;
	delete pSubtracao;
}
