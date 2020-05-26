#pragma once
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include < vcclr.h >
using namespace std;
#include "password_type.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

  #define RNUM( min, max ) rand() % (max - min + 1) + min 

  char * nac_string_convert( String __gc* str )
  {
    static char* buffer = new char [ str->Length + 1 ];
    const wchar_t __pin* p = PtrToStringChars(str);
    wcstombs(buffer, p, (str -> Length + 1) * 2);
    return buffer;
   }



namespace random_password_generator
{


	
	
	/// <summary> 
	/// Summary for edit_password
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class edit_password : public System::Windows::Forms::Form
	{
	public: 
		edit_password(void)
		{
			password_list = new vector<password_type>;
			password = new ostringstream();
			current = new password_type;
			InitializeComponent();
			changed = false;
		
		}

	private:  ostringstream* password;

		private:
		void gen_password(int length)
		{
		 char current = '*';
        
		  for( int i=0; i < length; ++i )
		  {
		   if( ascii->Checked == true )
		   {
		    current = RNUM( 33, 126 );
			*password << current;
		   }
		   else
           if( numbers->Checked == true && alphabet->Checked == true )
		   {
            char number = RNUM( 48, 57 );
			char letter;
			if( alphabet_case->Checked == true )
			{
			 letter = RNUM( 65, 90 );
			 if( RNUM(1,2) == 2 ) letter = tolower( letter );
			}
			else
			{
             letter = RNUM( 97, 122 );
			}
            
			if( RNUM(1,2) == 2 ) current = letter;
			else current = number;

			*password << current;
            
		   }
		   else
		   if( numbers->Checked == false && alphabet->Checked == true )
		   {
		    if( alphabet_case->Checked == true )
			{
			 current = RNUM( 65, 90 );
			 if( RNUM(1,2 ) == 2 ) *password << tolower( current );
			 else
				 *password << current;
			}
			else
			{
              current = RNUM( 97, 122 );
			  *password << current;
			}
		   }
		   else
		   if( numbers->Checked == true && alphabet->Checked == false )
		   {
             current = RNUM( 48, 57 );
			 *password << current;
		   }
		  }
		  
		}
        
	protected: 
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}
	public:  bool changed;
    public: vector<password_type>* password_list;


	private: password_type* current;
	private: System::Windows::Forms::TextBox *  description_text;

	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::TextBox *  password_text;
	private: System::Windows::Forms::Label *  label2;

	private: System::Windows::Forms::CheckBox *  new_password;
	private: System::Windows::Forms::CheckBox *  ascii;
	private: System::Windows::Forms::CheckBox *  numbers;
	private: System::Windows::Forms::CheckBox *  alphabet_case;
	private: System::Windows::Forms::CheckBox *  alphabet;
	private: System::Windows::Forms::Button *  save_button;
	private: System::Windows::Forms::StatusBar *  statusbar;
	private: System::Windows::Forms::NumericUpDown *  index;

	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::NumericUpDown *  password_length;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container* components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->new_password = new System::Windows::Forms::CheckBox();
			this->description_text = new System::Windows::Forms::TextBox();
			this->label1 = new System::Windows::Forms::Label();
			this->password_text = new System::Windows::Forms::TextBox();
			this->label2 = new System::Windows::Forms::Label();
			this->ascii = new System::Windows::Forms::CheckBox();
			this->numbers = new System::Windows::Forms::CheckBox();
			this->alphabet_case = new System::Windows::Forms::CheckBox();
			this->alphabet = new System::Windows::Forms::CheckBox();
			this->save_button = new System::Windows::Forms::Button();
			this->statusbar = new System::Windows::Forms::StatusBar();
			this->index = new System::Windows::Forms::NumericUpDown();
			this->password_length = new System::Windows::Forms::NumericUpDown();
			this->label3 = new System::Windows::Forms::Label();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->index))->BeginInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->password_length))->BeginInit();
			this->SuspendLayout();
			// 
			// new_password
			// 
			this->new_password->Location = System::Drawing::Point(24, 16);
			this->new_password->Name = S"new_password";
			this->new_password->Size = System::Drawing::Size(160, 16);
			this->new_password->TabIndex = 0;
			this->new_password->Text = S"Add New Password to List";
			this->new_password->CheckedChanged += new System::EventHandler(this, &random_password_generator::edit_password::new_password_CheckedChanged);
			// 
			// description_text
			// 
			this->description_text->Location = System::Drawing::Point(224, 56);
			this->description_text->Name = S"description_text";
			this->description_text->Size = System::Drawing::Size(400, 20);
			this->description_text->TabIndex = 1;
			this->description_text->Text = S"";
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(32, 56);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(80, 16);
			this->label1->TabIndex = 3;
			this->label1->Text = S"Description";
			// 
			// password_text
			// 
			this->password_text->Location = System::Drawing::Point(128, 96);
			this->password_text->MaxLength = 600;
			this->password_text->Multiline = true;
			this->password_text->Name = S"password_text";
			this->password_text->Size = System::Drawing::Size(496, 104);
			this->password_text->TabIndex = 4;
			this->password_text->Text = S"";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(72, 96);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(56, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = S"Password";
			// 
			// ascii
			// 
			this->ascii->Location = System::Drawing::Point(192, 248);
			this->ascii->Name = S"ascii";
			this->ascii->Size = System::Drawing::Size(296, 16);
			this->ascii->TabIndex = 19;
			this->ascii->Text = S"Any ASCII Character (includes numbers and alphabet)";
			this->ascii->CheckedChanged += new System::EventHandler(this, &random_password_generator::edit_password::ascii_CheckedChanged);
			// 
			// numbers
			// 
			this->numbers->Location = System::Drawing::Point(40, 248);
			this->numbers->Name = S"numbers";
			this->numbers->Size = System::Drawing::Size(120, 24);
			this->numbers->TabIndex = 18;
			this->numbers->Text = S"Numbers";
			this->numbers->CheckedChanged += new System::EventHandler(this, &random_password_generator::edit_password::numbers_CheckedChanged);
			// 
			// alphabet_case
			// 
			this->alphabet_case->Enabled = false;
			this->alphabet_case->Location = System::Drawing::Point(136, 216);
			this->alphabet_case->Name = S"alphabet_case";
			this->alphabet_case->Size = System::Drawing::Size(96, 24);
			this->alphabet_case->TabIndex = 17;
			this->alphabet_case->Text = S"case sensitive";
			this->alphabet_case->CheckedChanged += new System::EventHandler(this, &random_password_generator::edit_password::alphabet_case_CheckedChanged);
			// 
			// alphabet
			// 
			this->alphabet->Location = System::Drawing::Point(40, 216);
			this->alphabet->Name = S"alphabet";
			this->alphabet->Size = System::Drawing::Size(88, 24);
			this->alphabet->TabIndex = 16;
			this->alphabet->Text = S"Alphabet";
			this->alphabet->CheckedChanged += new System::EventHandler(this, &random_password_generator::edit_password::alphabet_CheckedChanged);
			// 
			// save_button
			// 
			this->save_button->Location = System::Drawing::Point(232, 304);
			this->save_button->Name = S"save_button";
			this->save_button->Size = System::Drawing::Size(128, 24);
			this->save_button->TabIndex = 20;
			this->save_button->Text = S"Done";
			this->save_button->Click += new System::EventHandler(this, &random_password_generator::edit_password::save_button_Click);
			// 
			// statusbar
			// 
			this->statusbar->Location = System::Drawing::Point(0, 344);
			this->statusbar->Name = S"statusbar";
			this->statusbar->Size = System::Drawing::Size(640, 22);
			this->statusbar->TabIndex = 21;
			// 
			// index
			// 
			this->index->Location = System::Drawing::Point(128, 56);
			this->index->Name = S"index";
			this->index->Size = System::Drawing::Size(88, 20);
			this->index->TabIndex = 22;
			this->index->ValueChanged += new System::EventHandler(this, &random_password_generator::edit_password::index_ValueChanged);
			// 
			// password_length
			// 
			this->password_length->Location = System::Drawing::Point(8, 184);
			this->password_length->Name = S"password_length";
			this->password_length->Size = System::Drawing::Size(64, 20);
			this->password_length->TabIndex = 23;
			this->password_length->ValueChanged += new System::EventHandler(this, &random_password_generator::edit_password::password_length_ValueChanged);
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(8, 128);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(88, 56);
			this->label3->TabIndex = 24;
			this->label3->Text = S"Generate New Password by Increasing Length";
			// 
			// edit_password
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(640, 366);
			this->ControlBox = false;
			this->Controls->Add(this->label3);
			this->Controls->Add(this->password_length);
			this->Controls->Add(this->index);
			this->Controls->Add(this->statusbar);
			this->Controls->Add(this->save_button);
			this->Controls->Add(this->ascii);
			this->Controls->Add(this->numbers);
			this->Controls->Add(this->alphabet_case);
			this->Controls->Add(this->alphabet);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->password_text);
			this->Controls->Add(this->description_text);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->new_password);
			this->Name = S"edit_password";
			this->Text = S"edit_password";
			this->Load += new System::EventHandler(this, &random_password_generator::edit_password::edit_password_Load);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->index))->EndInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->password_length))->EndInit();
			this->ResumeLayout(false);

		}		
	private: System::Void new_password_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
			 {
				 if( new_password->Checked == true )
				 {
				   index->Hide();
				 }
				 else
				 {
				  index->Show();
				 }
			 }

private: System::Void edit_password_Load(System::Object *  sender, System::EventArgs *  e)
		 {
          if( password_list->size() == 0 )
		  {

		  }
		  else
		  {
		   index->Maximum = (password_list->size()-1);
			 
		   alphabet->Checked = password_list->at(0).alphabet;
		   alphabet_case->Checked = password_list->at(0).alphabet_case;
		   numbers->Checked = password_list->at(0).number;
		   ascii->Checked = password_list->at(0).ascii;
		   password_text->Text = password_list->at(0).text.c_str();
		   description_text->Text = password_list->at(0).description.c_str();
		   password_length->set_Value( password_list->at(0).text.size() );
		  }
		  }

private: System::Void ascii_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
		  if( ascii->Checked == true )
		   {
             alphabet->Enabled = false;
			 numbers->Enabled = false;
			  statusbar->set_Text( "All ASCII Character will be allowed" );
		   }
		   else
		   {
             alphabet->Enabled = true;
			 numbers->Enabled = true;
			 statusbar->set_Text( "All ASCII Character not allowed" );
		   }
		 }

private: System::Void alphabet_case_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 if( alphabet_case->Checked == true )
		   {
			 statusbar->set_Text( "Lower and upper case alphabetic allowed" );
		   }
		   else
		   {
             statusbar->set_Text( "Lower case alphabetic allowed" );
		   }
		 }

private: System::Void alphabet_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			  if( alphabet->Checked == true )
		   {
            ascii->Enabled = false;
			alphabet_case->Enabled = true;
			statusbar->set_Text( "Lower case alphabetic Characters allowed" );
		   }
		   else
		   {
             ascii->Enabled = true;
			 alphabet_case->Enabled = false;
			 statusbar->set_Text( "Alphabetic Characters not allowed" );
		   }
		 }

private: System::Void numbers_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 if( numbers->Checked == true )
		   {
		     ascii->Enabled = false;
			 statusbar->set_Text( "Numbers allowed" );
		   }
		   else
		   {
		     ascii->Enabled = true;
			 statusbar->set_Text( "Numbers not allowed" );
		   }
		 }

private: System::Void save_button_Click(System::Object *  sender, System::EventArgs *  e)
		 {
		   changed = true;
           
             current->alphabet = alphabet->Checked;
			 current->alphabet_case = alphabet_case->Checked;
			 current->ascii = ascii->Checked;
			 current->number = numbers->Checked;
			 current->description = nac_string_convert( description_text->Text );
			 current->text = nac_string_convert( password_text->Text );

		 if( new_password->Checked == false )
		 {
			 password_list->at( Decimal::ToInt32(index->Value) ) = *current;
		 }
		 else
		 {
			 password_list->push_back( *current );
		 }
		   this->Hide();
		 }

private: System::Void index_ValueChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 *current = password_list->at( Decimal::ToInt32(index->Value) );
		   alphabet->Checked = current->alphabet;
		   alphabet_case->Checked = current->alphabet_case;
		   numbers->Checked = current->number;
		   ascii->Checked = current->ascii;
		   password_text->Text = current->text.c_str();
		   description_text->Text = current->description.c_str();
		   password_length->set_Value( current->text.size() );
		}

private: System::Void password_length_ValueChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 gen_password( Decimal::ToInt32( password_length->Value ) );
			 password_text->set_Text( password->str().c_str() );
			 password->str(" ");
		 }

};
}