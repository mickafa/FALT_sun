#include <bits/stdc++.h>
using namespace std;
#define N (120)         /// кол-во точек в общем массиве
#define T0 (283.0)      /// эталонные температура,
#define P0 (101.0)      /// давление,
#define ALPHA0 (34.5)   /// угол рефракции
double da = (-0.01);    /// начальный шаг по коэффициенту а
double db = (0.01);     /// и по b
double t[N];            /// архив измерений температуры
double p[N];            /// давления
double alpha[N];        /// угла рефракции

/// вычисление среднеквадратичного отклонения (дисперсии)
/// при данных коэффициентах a и b
double f ( double a, double b ){
    double c, s = 0.0;
    c = ALPHA0 - a*T0 - b*P0;    /// свободный коэфф с
    for ( int i = 0; i < N; i++ ){
        double x;
        x = a*t[i] + b*p[i] + c - alpha[i];
        s += x*x;
    }
    return s/N;
}

int main (){
    FILE *fp;

/// читаем первую часть общего массива (по давлению)
    fp = fopen ( "refraction_pressure.csv", "r" );
    assert ( fp );
    for ( int i = 0; i < N/2; i++ ){
        fscanf ( fp, "%le,%le", &p[i], &alpha[i] );
        t[i] = T0;
    }
    fclose ( fp );

/// читаем вторую часть общего массива (по температуре)
    fp = fopen ( "refraction_temperature.csv", "r" );
    assert ( fp );
    for ( int i = N/2; i < N; i++ ){
        fscanf ( fp, "%le,%le", &t[i], &alpha[i] );
        p[i] = P0;
    }
    fclose ( fp );
/// a, b, c - коэффициенты ур-я плоскости
/// и две временные переменные
    double a = 0., b = 0., c, temp, tempNew;

/// ищем наилучшее сочетание a и b методом градиентного спуска
/// 6 итераций оказалось достаточно
    for ( int j = 0; j < 6; j++ ){
        printf ( "%2d\ta=%.7lf\tb=%.7lf\tDis=%.7lf\n", j, a, b, f ( a, b ) );

/// находим наилучшее значение а при данном шаге da
        temp = f ( a, b );
        for ( a += da; (tempNew = f ( a, b )) < temp; a += da ) temp = tempNew;
        da *= -0.1; /// уменьшаем da в 10 раз
                    /// и меняем направление шага


/// находим наилучшее значение а при данном шаге da
        temp = f ( a, b );
        for ( b += db; (tempNew = f ( a, b )) < temp; b += db ) temp = tempNew;
        db *= -0.1; /// уменьшаем db в 10 раз
                    /// и меняем направление шага
    }

/// получены коэффициенты a, b, c ур-я плоскости и сигма
    printf ( "a=%.7lf\tb=%.7lf\tc=%.7lf\tsigma=%.7lf\n", a, b, c = ALPHA0 - a*T0 - b*P0, sqrt(f ( a, b )) );
    printf ( "calculation finished\n\n" );

/// переход в интерактивный режим
    while (1){
        double tx, px;
        printf ( "\nEnter T(K), p(kPa) " );
        scanf ( "%lf%lf", &tx, &px );
        printf ( "Refraction angle = %.2lf minutes", a*tx + b*px + c );
    }

    return 0;
}
