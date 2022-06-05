#include <iostream>
#include <vector>
#include "histogram.h"

using namespace std;

vector<double>
input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

vector<size_t>
make_histogram(const vector<double>& numbers, size_t bin_count, double min, double max){
    vector<size_t>result (bin_count);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count) {
            bin--;
        }
        result[bin]++;
    }
    return result;
}

void
show_histogram_text(const auto bins){
    const auto SCREEN_WIDTH = 80;
    const auto MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins) {
        if (bin < 100) {
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }

}

void svg_line2(size_t X1,size_t Y1,size_t X2,size_t Y2,string stroke,size_t wid,ostream &stream)
{
stream<<"<line x1='"<<X1<<"' y1='"<<Y1<<"' x2='"<<X2<<"' y2='"<<Y2<<"' stroke='"<<stroke<<"' stroke-width='"<<wid<<"' stroke-dasharray = '10 10'/>";
}

void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='"<< baseline<< "'>"<<text<<"</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill){
    cout<< "<rect x= '" << x <<"' y='"<< y << "' width='"<<width<<"' height='" << height << "' stroke='"<< stroke<<"' fill='"<<fill<<"' />\n ";
}

void
svg_end() {
    cout << "</svg>\n";
}

void
show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double MAX_WIDTH = (IMAGE_WIDTH - TEXT_WIDTH);
    size_t max_bin = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bin)
        {
            max_bin = bin;
        }
    }
    svg_begin(400, 300);
    double top = 0;
    double top2 =0;
    svg_line2(top, top, IMAGE_WIDTH, top , "black", 10, cout);
    for (size_t bin : bins) {
        top += BIN_HEIGHT;
        double bin_width = BLOCK_WIDTH * bin;
        if (max_bin > (MAX_WIDTH/BLOCK_WIDTH))
        {
            bin_width = (MAX_WIDTH-15) * (static_cast<double>(bin) / max_bin);
        }
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "black");
}
top += 2*BIN_HEIGHT;
svg_line2(10, top, IMAGE_WIDTH, top , "black", 10, cout);
svg_line2(top2, top2, top2, top , "black", 10, cout);
svg_line2(IMAGE_WIDTH, top2, IMAGE_WIDTH, top , "black", 10, cout);
    svg_end();
}

int main() {
    // ���� ������
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr<<"Enter numbers:";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    // ��������� ������
    double min, max;
    find_minmax(numbers, min, max);

    const auto bins = make_histogram(numbers, bin_count, min, max);

    show_histogram_svg(bins);

    return 0;
}


