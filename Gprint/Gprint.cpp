#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
//a.txt
//ac, dg, er, eds, d, df
//14, 5f, 56, ff3, fdff, fsd
//15, gg, 34, dfd, 34e, er
//35, re, 434, rer, 34, er

//b.txt
//12, wd, wr, sd, sf, 34.5676
//23, er, df, xc, xc, 12.234

//��׼�����������%[]��%n˵������ʹ�÷���
//scanf fscanf, ���ӵ�һ���ǿո�Ŀ���ʾ�ַ���ʼ����
//��׼�����������scanf������Խ϶��ת��˵��������������Ϊ���ż����������ڸ��ֽ̲��С�����ֵ��ǣ�[]��n�����ֶ�Ϊc89 / c99���涨�ı�׼˵����ȴ�����ڴ�����̲��г��֡���Ȼ[]��n˵������ʹ��Ƶ�ʲ�������˵�������������ڳ�������е�������Ȼ����С�ӣ�������[]˵������
//������֮��scanf�Կհ��ַ�Ϊ������������������ַ������������ַ�Ϊ������ģ�����ô�죿[]����ר�Ŵ�����������ת��˵������[]ת��˵��������ͨ�����ַ�ʽ��������ַ����������һ��[�ַ��ұ�û���������^������ô����[]֮����ַ����ǽ���ַ������������еĿ������ַ�����Ϊ�������������[���Ž���һ���������^������ô�����෴��^��]֮����ַ��Ƕ����������������ַ��ǽ���ַ�����
//��ʹ��[]˵����֮ǰ�����������������һ��ɨ���б�ɨ���б�scanlist��ָ���ǰ�����[��]�����ַ�֮����������[�ַ��������֮����ַ������磺
//scanf("%[abcd]", ptr);
//abcd���ɨ���б�����ɨ���ַ�����scanset����ɨ���ַ���ָ���ǽ���ַ�����������������ӣ�����ַ�������abcd���������һ���ַ�����cbadkjf������ôptr�õ����ַ�����cbad��kjf�����ַ������ڶ���������뵽k�ַ�ʱ�����ַ������ضϣ�kjf�����ַ�������stdin���档�����������������磺
//scanf("%[^abcd]", ptr);
//ɨ���б���Ȼ��abcd����ɨ���ַ����ǳ�abcd��Ŀ������ַ�����������ַ�����jksferakjjdf����ptr�õ����ַ����ǡ�jksfer������������������ַ������ַ�������������s˵������������[]ǰ��ʹ��λ�����磺
//scanf("[^abcd]", ptr);
//��������ַ������ֻ�ܰ���10���ַ�����'\0'�ַ��⣩��
//[���ſ�����Ϊɨ���б��е�һ����Ա����]�ַ�����������ߵ�[�ַ����������������⣬��������¶����ᱻ����ɨ���б�ĳ�Ա�����硰%[]abcd]�����ߡ�%[^]abcd]�����������������]�ַ�����ɨ���б�ĳ�Ա��������ǡ�%[ab]cd]�����м��]�ַ����ᱻ����ɨ���б�ĳ�Ա��������������Ľ���������߰���ġ�
//���ڼ��� - ��ֻ���ڽ���[�ַ��������ַ��Լ���Ϊɨ���б����һ����Աʱ�� - �ַ��Żᱻ��Ϊɨ���б�ĳ�Ա��c��׼����������涨Ϊ��������صġ����������������������ļ��Ŷ���Ϊ���ַ������磺
//scanf("%[a-zA-Z]", ptr);
//��ôɨ���б��ɴ�Сд��26����ĸ��ɡ������������Ծɰ���������µļ�����Ϊɨ���б��Ա��
//fscanf(fd, "%*[^\n]\n");//%*�������û�д棬ֻ����ָ�����������������
//%n˵���������Ч�ַ�������%n��scanf��printf�ж���ʹ�á���%n���Ӧ���β���һ��int���͵�ָ�룬%n��Ӱ��scanf��printf�ķ���ֵ�����磺
//scanf("%d %d%n", &i, &j, &k);
//�������434 6434����k����8����scanf�ķ���ֵ��ȻΪ2�����磺
//scanf("%c%n", &ch, &k);
//���롰sbcdefdg����k����1��������8����Ϊ%cֻȡһ���ַ���%n���������Ч�ַ�������
//%n����printf�������ʾ������ַ����������磺
//printf("i=%d, j=%d\n%n", i, j, &k);
//��i = 343��j = 123������£�k = 12��ͬʱ%n��Ӱ��printf�ķ���ֵ���䷵��ֵ��ȻΪ12��������14��
//== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
//����÷�����H264 jm82�ο������Ͽ����ģ������ӽ��������������ļ��ж�ȡ���ò������������£�
//// read the decoder configuration file
//if ((fd = fopen(config_filename, "r")) == NULL)
//{
//	snprintf(errortext, ET_SIZE, "Error: Control file %s not found\n", config_filename);
//	error(errortext, 300);
//}
//fscanf(fd, "%s", inp->infile);                // H.26L compressed input bitsream
//fscanf(fd, "%*[^\n]");
//fscanf(fd, "%s", inp->outfile);               // YUV 4:2:2 input format
//fscanf(fd, "%*[^\n]");
//fscanf(fd, "%s", inp->reffile);               // reference file
//fscanf(fd, "%*[^\n]");
//��Ӧ�������ļ��������£�
//test.264                 ........H.26L coded bitstream
//test_dec.yuv             ........Output file, YUV 4:2 : 0 format
//test_rec.yuv             ........Ref sequence(for SNR)
//ͨ�����ַ�ʽ
//inp->infile = "test.264"
//inp->outfile = "test_dec.yuv"
//inp->reffile = "test_rec.yuv"
//����Ӧ�������ļ��е�һЩע���򲻻ᱻ���룬�����൱�����÷�������ͨ���ϸ�Լ��ע�ͷ�������һ���ַ�һ���ַ������������ַ�ʽ������ֵ࣡�ý��

int main(void)
{
	vector<string> mstr;
	FILE *fp = fopen("a.txt", "rt");
	while (!feof(fp))
	/*char chA[2048];
	char chB[2048], chC[2048], chD[2048], chE[2049], chF[2048];*/
	//while(EOF != fscanf(fp, "%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000]", chA, chB, chC, chD, chE, chF))
	{
		char chA[2048];
		char chB[2048], chC[2048], chD[2048], chE[2049], chF[2048];
		/************************************************************************/
		/* fscanf���� ��d.dat��������430301wang56.345,��fscanf(fp,"%d%s%f",&a,name,&f)�� ���sΪwang56.345  
		   fscanf(fp, "%*d%[a-zA-Z]%f", name, &f);  //%*d�Թ���һ���� �ڶ���ɨ����ȡ�ַ� ʣ�µ��Ҳ��ý����˰�
		   
		   #include <stdio.h>
		   main()
		   {
		   int i;
		   unsigned int j;
		   char s[5];
		   fscanf(stdin, "%d %x %5[a-z] %*s %f", &i, &j, s, s);
		   printf("%d %d %s \n", i, j, s);
		   }

		   ִ�У�
		   10 0x1b aaaaaaaaa bbbbbbbbbb //�Ӽ�������
		   10 27 aaaaa
		   */
		/************************************************************************/


		//��һ������ִ�и�ʽ������,fscanf�����ո�ͻ���ʱ������ע��ո�ʱҲ����

		/*fscanf(fp, "%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z]", chA, chB, chC, chD, chE, chF);
		printf("%s\n", chA);
		printf("%s\n", chB);
		printf("%s\n", chC);
		printf("%s\n", chD);
		printf("%s\n", chE);
		printf("%s\n", chF);*/


		/*	int nAge = 0;
			double dGrade = 0.0;
			fscanf(fp, "%d,%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%lf", &nAge, chB, chC, chD, chE, &dGrade);
			printf("%d\n", nAge);
			printf("%s\n", chB);
			printf("%s\n", chC);
			printf("%s\n", chD);
			printf("%s\n", chE);
			printf("%f\n", dGrade);*/

		/*fscanf(stream, "%[^\n]%*c", line)*/

		//���Ƕ�ȡһ������
		//FILE *stream;
		//char line[80];

		//while ((fscanf(stream, "%[^\n]", line)) != EOF)
		//{
		//	printf("Line = %s \n", line);
		//}
		//The following code example demonstrates the second method above to work around this problem:
		//FILE *stream;
		//char line[80];

		//while ((fscanf(stream, "%[^\n]", line)) != EOF)
		//{
		//	fgetc(stream);    // Reads in '\n' character and moves file
		//					  // stream past delimiting character
		//	printf("Line = %s \n", line);
		//}

		int nAge = 0;
		double dGrade = 0.0;
		//fscanf(fp, "%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z]", chA, chB, chC, chD, chE, chF);
		//fscanf(fp, "%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000]", chA, chB, chC, chD, chE, chF);
		fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", chA, chB, chC, chD, chE, chF);
		printf("%s\n", chA);
		mstr.push_back(chA);
		printf("%s\n", chB);
		mstr.push_back(chB);
		printf("%s\n", chC);
		mstr.push_back(chC);
		printf("%s\n", chD);
		mstr.push_back(chD);
		printf("%s\n", chE);
		mstr.push_back(chE);
		printf("%s\n", chF);
		mstr.push_back(chF);

		fgetc(fp);


		//while(fscanf(fp, "%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000]", chA, chB, chC, chD, chE, chF) != EOF)
	/*	{
			printf("%s\n", chA);
			printf("%s\n", chB);
			printf("%s\n", chC);
			printf("%s\n", chD);
			printf("%s\n", chE);
			printf("%s\n", chF);
		}
*/
	}
	system("pause");
	return 0;
}