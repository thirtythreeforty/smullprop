/* HELICAL
 * Copyright 2013 George Hilliard
 * Based upon PROP97C by Ed Smull
 * Designs layout of 0.75 inch blank for helical prop
 * Last revised: May 2013
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>

using namespace std;

int main()
{
    cout << "HELICAL      By George Hilliard V     Based upon PROP97C by Ed Smull" << endl
         << "Revised May 2013" << endl << endl;
    cout << "This program is free software: you can redistribute it and/or modify" << endl
         << "it under the terms of the GNU General Public License as published by" << endl
         << "the Free Software Foundation, version 3." << endl << endl;

    // INPUT AND MATH
    // Most of this code was translated directly from the original program.
    string strE, strD;
    float d, P;
    cout << "Date? "; getline(cin, strE);
    cout << "Application? "; getline(cin, strD);
    cout << "Diameter? "; cin >> d;
    cout << "Pitch? "; cin >> P;

    cout << endl;
    cout << "C1 is the distance from centerline to leading edge." << endl;
    cout << "C2 is the distance from centerline to trailing edge." << endl;
    cout << endl;

    // I'm not familiar with this program's meaning (I'm just
    // the translator!) so unfortunately I can't give these
    // variables more meaningful names.
    float R[int(d)+2], C[2][int(d)+2], T[int(d)+2], B[2][int(d)+2], W[2][int(d)+2], D[2][int(d)+2];
    float B1 = .76236, H = .75;
    float Poverd = P / d;
    // Ideally, we'd start from 0.  In practice, starting at 1 makes the math much easier.
    for(int n = 1; n <= d; ++n) {
        R[n] = float(n)/2;
        cout << "Radius = " << R[n] << endl;
        cout << "C1? "; cin >> C[0][n];
        cout << "C2? "; cin >> C[1][n];

        T[n] = P / (2 * 3.141592654 * R[n]);
        B[1][n] = atan(T[n]) - B1;
        B[0][n] = atan(T[n]) * 57.297;
        W[0][n] = C[0][n] * cos(B[1][n]);
        W[1][n] = C[1][n] * cos(B[1][n]);
        D[0][n] = H / 2 + C[0][n] * sin(B[1][n]);
        D[1][n] = H / 2 - C[1][n] * sin(B[1][n]);
    }

    // CREATE OUTPUT
    stringstream out;
    out << "       DESIGN LAYOUT FOR HELICAL PROP USING 3/4-INCH BLANK" << endl << endl;
    out << "Date: " << strE << endl << endl;
    out << "Application: " << strD << endl << endl;
    out << "Diameter = " << d << " inches" << endl << endl;
    out << "Pitch = " << P << " inches" << endl << endl;
    out << "Pitch / Diameter = " << Poverd << endl << endl;

    // Ugh, formatting output in C++ isn't very pretty.
    out << "    Radius    Beta      C1      C2     D1     D2     W1     W2"    << endl;
    out << "------------------------------------------------------------------" << endl;

    out << fixed;

    for(int n = 1; n <= d; ++n) {
        out << setprecision(1) << right;
        out << setw(10) << R[n] << "    ";

        out << setprecision(2) << left;
        out << setw(10) << B[0][n];

        out << setw(8) << C[0][n];
        out << setw(7) << C[1][n];
        out << setw(7) << D[0][n];
        out << setw(7) << D[1][n];
        out << setw(7) << W[0][n];
        out << setw(7) << W[1][n] << endl;
    }
    out << endl;
    out << "C1 is the distance from centerline to leading edge." << endl;
    out << "C2 is the distance from centerline to trailing edge." << endl;
    out << "Beta is the local blade angle in degrees." << endl;
    out << "D1 and D2 are LE and TE offsets on the sides of the blank." << endl
        << "   They are measured from the bottom (aft) face of the blade." << endl;
    out << "W1 and W2 are the blank widths from centerline to LE and TE." << endl;

    // DISPLAY AND SAVE
    cout << endl << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << out.str();
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    char yn;
    do {
        while((yn = getchar()) != '\n' && yn != EOF)
            ; // discard newlines, etc.
        cout << "Save this listing to a file? [y/n] ";
        cin.get(yn);
    } while(yn != 'y' && yn != 'Y' && yn != 'n' && yn != 'N');

    if(yn == 'y' || yn == 'Y') {
        string filename;
        while((yn = getchar()) != '\n' && yn != EOF)
            ; // discard newlines, etc.
        cout << "Enter the file name to save this listing as: " << endl;
        getline(cin, filename);
        if(filename == "") filename = "helical.txt";
        else filename += ".txt";
        ofstream f;
        f.open(filename.c_str());
        f << out.str();
        f.close();
    }

    return 0;
}
