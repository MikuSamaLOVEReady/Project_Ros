/******************** (C) COPYRIGHT 2022 Geek************************************
* File Name          : Mat.h
* Current Version    : V1.0
* Author             : logzhan
* Date of Issued     : 2022.09.14
* Comments           : �����ľ������
********************************************************************************/
/* Header File Including -----------------------------------------------------*/
#ifndef _H_MAT_
#define _H_MAT_

#define MAT_MAX 15 //�������ܴ�����������


#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

class Mat
{
public:
	Mat();
	Mat(int setm,int setn,int kind);//kind=1��λ��kind=0�����,��������ʼ�����ݡ�
	void Init(int setm,int setn,int kind);//kind=1��λ��kind=0�����,��������ʼ�����ݡ�

	void Zero(void);
	//��Щ�ؼ�����Ӧ����Ϊprivate�ġ�����Ϊ�˷��㣬��Ҳ������public
	int m;//����
	int n;//����
	double mat[MAT_MAX][MAT_MAX];//������������

	//����ľ���
	Mat SubMat(int a,int b,int lm,int ln);//��ȡ����һ����
	void FillSubMat(int a,int b,Mat s);//����Ӿ���

	//����ר��
	double absvec();//����������ĳ��ȡ����Ǹ���Ԫ�صľ���ֵ��
	double Sqrt();//�������ȵ�ƽ��
	friend Mat operator ^(Mat a,Mat b);//���

	//����
	friend Mat operator *(double k,Mat a);
	friend Mat operator *(Mat a,double k);
	friend Mat operator /(Mat a,double k);
	friend Mat operator *(Mat a,Mat b);
	friend Mat operator +(Mat a,Mat b);
	friend Mat operator -(Mat a,Mat b);
	friend Mat operator ~(Mat a);//ת��	
	friend Mat operator /(Mat a,Mat b);//a*inv(b)
	friend Mat operator %(Mat a,Mat b);//inv(a)*b

	//MAT inv();//�����

private:
	// Ϊ���ø�˹��Ԫ��������һЩ����
	// ��������
	void RowExchange(int a, int b);
	// ĳһ�г���ϵ��
	void RowMul(int a,double k);
	// ��ĳһ�мӼ���һ�еı���
	void RowAdd(int a,int b, double k);
	// ��������
	void ColExchange(int a, int b);
	// ĳһ�г���ϵ��
	void ColMul(int a,double k);
	// ��ĳһ�мӼ���һ�еı���
	void ColAdd(int a,int b,double k);
	

};






#endif






