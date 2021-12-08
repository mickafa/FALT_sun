#include <bits/stdc++.h>
using namespace std;
#define N (120)         /// ���-�� ����� � ����� �������
#define T0 (283.0)      /// ��������� �����������,
#define P0 (101.0)      /// ��������,
#define ALPHA0 (34.5)   /// ���� ���������
double da = (-0.01);    /// ��������� ��� �� ������������ �
double db = (0.01);     /// � �� b
double t[N];            /// ����� ��������� �����������
double p[N];            /// ��������
double alpha[N];        /// ���� ���������

/// ���������� ������������������� ���������� (���������)
/// ��� ������ ������������� a � b
double f ( double a, double b ){
    double c, s = 0.0;
    c = ALPHA0 - a*T0 - b*P0;    /// ��������� ����� �
    for ( int i = 0; i < N; i++ ){
        double x;
        x = a*t[i] + b*p[i] + c - alpha[i];
        s += x*x;
    }
    return s/N;
}

int main (){
    FILE *fp;

/// ������ ������ ����� ������ ������� (�� ��������)
    fp = fopen ( "refraction_pressure.csv", "r" );
    assert ( fp );
    for ( int i = 0; i < N/2; i++ ){
        fscanf ( fp, "%le,%le", &p[i], &alpha[i] );
        t[i] = T0;
    }
    fclose ( fp );

/// ������ ������ ����� ������ ������� (�� �����������)
    fp = fopen ( "refraction_temperature.csv", "r" );
    assert ( fp );
    for ( int i = N/2; i < N; i++ ){
        fscanf ( fp, "%le,%le", &t[i], &alpha[i] );
        p[i] = P0;
    }
    fclose ( fp );
/// a, b, c - ������������ ��-� ���������
/// � ��� ��������� ����������
    double a = 0., b = 0., c, temp, tempNew;

/// ���� ��������� ��������� a � b ������� ������������ ������
/// 6 �������� ��������� ����������
    for ( int j = 0; j < 6; j++ ){
        printf ( "%2d\ta=%.7lf\tb=%.7lf\tDis=%.7lf\n", j, a, b, f ( a, b ) );

/// ������� ��������� �������� � ��� ������ ���� da
        temp = f ( a, b );
        for ( a += da; (tempNew = f ( a, b )) < temp; a += da ) temp = tempNew;
        da *= -0.1; /// ��������� da � 10 ���
                    /// � ������ ����������� ����


/// ������� ��������� �������� � ��� ������ ���� da
        temp = f ( a, b );
        for ( b += db; (tempNew = f ( a, b )) < temp; b += db ) temp = tempNew;
        db *= -0.1; /// ��������� db � 10 ���
                    /// � ������ ����������� ����
    }

/// �������� ������������ a, b, c ��-� ��������� � �����
    printf ( "a=%.7lf\tb=%.7lf\tc=%.7lf\tsigma=%.7lf\n", a, b, c = ALPHA0 - a*T0 - b*P0, sqrt(f ( a, b )) );
    printf ( "calculation finished\n\n" );

/// ������� � ������������� �����
    while (1){
        double tx, px;
        printf ( "\nEnter T(K), p(kPa) " );
        scanf ( "%lf%lf", &tx, &px );
        printf ( "Refraction angle = %.2lf minutes", a*tx + b*px + c );
    }

    return 0;
}
