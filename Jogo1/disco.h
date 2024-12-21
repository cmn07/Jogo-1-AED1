#pragma once
class disco
{
private:
	int tamanho; /* tamanho do disco */
	disco* proximo; /* ponteiro para o pr�ximo disco */
public:
	disco(int);
	int getTamanho() const;
	disco* getProximo() const;
	void setTamanho(int);
	void setProximo(disco*);
};

