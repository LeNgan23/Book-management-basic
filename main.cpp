#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

// Hàm chọn lựa
int bookOptions() 
{
	cout << "1. Thêm 1 cuốn sách"<< endl;
    cout << "2. Tìm 1 cuốn sách"<< endl;
    cout << "3. Tìm và chỉnh sửa 1 cuốn sách"<< endl;
    cout << "4. Danh sách sách"<< endl;
	cout << "0. Thoát"<< "\n\n";
	cout << "Yêu cầu của bạn là" << endl;
	cout << "Chọn số: ";

	int selectedOption = 0;
	cin >> selectedOption;
	cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); 

	return selectedOption;
}


void nhapsach() 
{
	string tensach, tacgia, chitietsach, line, namxuatban;
	int count = 0;
    
    cout << "______________________________________________________\n";
    cout << "\t********* Thông tin sách *********" << endl;
	cout << "Tên sách: ";
	getline(cin, tensach);
	cout << "Tác giả: ";
	getline(cin, tacgia);
    cout << "Năm xuất bản: ";
    getline(cin, namxuatban);
    cout << "\n";
	
    // Dò số sách có trong kho
	ifstream countData("library.dat");
	while (getline(countData, line)) 
    {
		count++;
	}

	countData.close();

	// Cho phép điền thông tin sách
	ofstream writeToLibrary;

    writeToLibrary.open("library.dat", ios::app);

	chitietsach = tensach + "\t\t" + tacgia + "\t\t" + namxuatban;
	// Nhập dữ liệu
	writeToLibrary << chitietsach << endl;

	// Đóng file đang mở
    writeToLibrary.close();

    cout << "Cuốn sách thứ " <<count + 1 << endl;
	cout << "Tên sách\t\t" << "Tác giả\t\t" << "NXB";
   	cout <<":"<< endl<< chitietsach << endl; 
}

void timsach () 
{
    cout << "______________________________________________________\n";
	cout << "\t******** Tìm một cuốn sách ******** \n" << endl;
	string tensach;
	cout << "Tên sách cần tìm: ";
	cin >> tensach;
    cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); 

	ifstream data("library.dat");
	ofstream temp;

    // file tạm thời
	temp.open("temp.dat", ios::app); 
    if(!data || !temp)
    {
        cout << "Sai thông tin!" << endl;
        return;
    }

    string strTemp;
    while(getline(data, strTemp))
    {   
		size_t found = strTemp.find(tensach); 
		if (found != string::npos) 
        {
            cout <<endl << "Tên sách\t\t" << "Tác giả \t\t" << "NXB" <<"\n";
			cout << strTemp << endl; 
        }
        
    }    
    data.close();
	temp.close();
}

void chinhsuasach() 
{
    cout << "___________________________________________________\n";
	cout << "******** Tìm và chỉnh sửa sách đã có ******** " << "\n\n";
	string tensach;
	cout << "Nhập tên sách cần tìm và chỉnh sửa: ";
	cin >> tensach;
	cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); 

	bool bookExist = false;
	ifstream data("library.dat");
	ofstream temp;

    // file tạm thời
	temp.open("temp.dat", ios::app); 
    if(!data || !temp)
    {
        cout << "Sai thông tin!" << endl;
        return;
    }

    // Tìm và chỉnh sửa sách đã chọn
	string strTemp;
    while(getline(data, strTemp))
    {   
		size_t found = strTemp.find(tensach); 
		if (found != string::npos) 
        {
			string tensachmoi, tacgiamoi, namxuatbanmoi;
            cout << "Sách: " << strTemp << endl; 
			cout << "Tên sách mới: ";
			getline(cin, tensachmoi);
			cout << "Tên tác giả mới: ";
			getline(cin, tacgiamoi);
            cout << "Năm xuất bản mới: ";
            getline(cin, namxuatbanmoi);

			strTemp = tensachmoi + "\t\t" + tacgiamoi + "\t\t" +namxuatbanmoi;
            cout << "\n";
		    cout << "Thông tin sách đã được cập nhật" << endl; 
            cout << "Sách: " << strTemp << endl;
			bookExist = true;
		}
		temp << strTemp << endl;
	}

	data.close();
	temp.close();

    if(bookExist) 
    {
		// xóa sách cũ
		if( remove( "library.dat" ) != 0 )
			perror( "Lỗi!!! Không thể xóa" );

		// đổi tên và lưu sách mới
		if ( rename("temp.dat", "library.dat")) 
        {
			perror("Error renaming");
			return;
		}
        cout << "\n";
	} else cout << "Không tìm thấy cuốn sách có tên: " << tensach << endl;	
}

void xuatsach() 
{
    cout << "________________________________________________\n";
	cout << "****** danh sách các cuốn sách hiện có ******" << endl;
    cout << "Tên sách\t\t" << "Tác giả\t\t" << "NXB"<< endl;
	ifstream data("library.dat");
    string row;
    while(getline(data, row))
    {   
        cout << row << endl;
    }
}

// Các hoạt động
void bookActions(int option) 
{
	switch(option) 
    {
		case 1: 
			nhapsach();
			break;
		case 2: 
			timsach();
			break;
        case 3:
            chinhsuasach();
			break;    
		case 4: 
			xuatsach();
			break;
	}
}

// Xét điều kiện của bookoptions
void home () 
{
	int option = bookOptions();
	if (option != 0 && option <= 4) 
    {
		bookActions(option);
	} 
    else if (option > 4) 
    {
		cout << endl << "!!! Mời chọn lại yêu cầu !!!" << endl;
		option = bookOptions();
	} 
    else 
    {
	 	exit(0);
	}
}


int main ()
{	
	while(true) 
    {
        cout << "\t__________________________________________\n\n";
		cout << "✩✩✩✩✩  Chương trình quản lý thư mục sách  ✩✩✩✩✩" << "\n\n";
		home();
        cout << "\t__________________________________________\n";
		cout << endl << "\t     Chọn yêu cầu tiếp theo của bạn"<<endl ;
        continue;
        
    }
	return 0;
}