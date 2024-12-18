#pragma once
class disco
{
private:
	int tamanho; /* tamanho do disco */
	disco* próximo; /* ponteiro para o próximo disco */
public:
	disco(int);
	int getTamanho() const;
	disco* getProximo() const;
	void setTamanho(int);
	void setProximo(disco*);
};

