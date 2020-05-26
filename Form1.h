#pragma once
#include <sstream>
#include <fstream>
#include <cctype>
#include <list>
#include <vector>
#include "password_display.h"
#include "edit_password.h"
#include "password_type.h"
#include "about_box.h"
#define RNUM( min, max ) rand() % (max - min + 1) + min 
using namespace std;

#define PASSWORD_FILE "passwords.txt"
#define HTML_PASSWORD_FILE "passwords.html"





namespace random_password_generator
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	

	/// <summary> 
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class Form1 : public System::Windows::Forms::Form
	{	
	public:
		Form1(void)
		{
			password = new ostringstream(100);
			current = new password_type;
			password_list = new list<password_type>;
			edit_form    = new random_password_generator::edit_password();
			password_box = new random_password_generator::password_display();
			about_form = new random_password_generator::about_box();
			InitializeComponent();
		}
	private: password_type* current;
	private: ostringstream* password;
	private: random_password_generator::edit_password* edit_form; // edit form
	private: random_password_generator::password_display* password_box; // password box
	private: random_password_generator::about_box* about_form; //about form
	private: System::Windows::Forms::MainMenu *  mainMenu1;
	private: System::Windows::Forms::MenuItem *  menuItem1;


	private: System::Windows::Forms::MenuItem *  menuItem4;
	private: System::Windows::Forms::MenuItem *  menuItem5;
	private: System::Windows::Forms::MenuItem *  edit_password_menuitem;
	private: System::Windows::Forms::MenuItem *  save_menuitem;
	private: System::Windows::Forms::MenuItem *  exit_menuitem;

	private: list<password_type>* password_list;

	private:
		void write_html_password_list(void)
		{
		  ofstream fout;
		  fout.open( HTML_PASSWORD_FILE );

		  fout<< "<html>\n"
			  << "<head>\n"
			  << "<title> Password List </title>\n"
			  << "</head>\n"
			  << "<body>\n"
			  << "<table style=\"text-align: left; width: 100%;\" border=\"0\" cellpadding=\"0\" cellspacing=\"10\">\n"
			  << "<tbody>\n"
			  << "<tr>\n"
			  << " <td><big><span style=\"font-weight: bold;\">Description</span></big></td>\n"
              << " <td><big><span style=\"font-weight: bold;\">Password</span></big></td>\n"
              << " <td><big><span style=\"font-weight: bold;\">Number</span></big></td>\n"
              << " <td><big><span style=\"font-weight: bold;\">Alphabet</span></big></td>\n"
              << " <td style=\"font-weight: bold;\"><big>Case Sensitive</big></td>\n"
              << " <td style=\"font-weight: bold;\"><big>ASCII</big></td>\n"
			  << "</tr>\n";
                 
            for(  list<password_type>::iterator marker = password_list->begin();  marker != password_list->end(); ++marker )
			{
			  fout<< "<tr>\n"
				  << "<td>" << marker->description << "</td>\n"
				  << "<td>" << marker->text << "</td>\n";

			  if( marker->number == false ) fout<< "<td>false</td>\n"; else fout<< "<td>true</td>\n";
			  if( marker->alphabet == false ) fout<< "<td>false</td>\n"; else fout<< "<td>true</td>\n";
			  if( marker->alphabet_case == false ) fout<< "<td>false</td>\n"; else fout<< "<td>true</td>\n";
			  if( marker->ascii == false ) fout<< "<td>false</td>\n"; else fout<< "<td>true</td>\n";

			  fout<< "</tr>\n";
			}

             fout<< "</tbody>\n"
                 << "</table>\n"
                 << "<br>\n"
				 << "</body>\n"
			     << "</html>\n";

			 fout.close();
		
			}

	
	private:
		void write_password_list(void)
		{
			ofstream fout;
			fout.open( PASSWORD_FILE );
			fout<<password_list->size()<<"\n";
            for(  list<password_type>::iterator marker = password_list->begin();  marker != password_list->end(); ++marker )
			{
              fout<<marker->text<<"\n";
			  fout<<marker->description<<"\n";
			  fout<<marker->number<<"\n";
			  fout<<marker->alphabet<<"\n";
			  fout<<marker->alphabet_case<<"\n";
			  fout<<marker->ascii<<"\n";
			}
			fout.close();
		}

	private: 
		void load_password_list(void)
		{
         ifstream fin;
		 string temp;
	     int list_length(0);
		
		 fin.open( PASSWORD_FILE );
        
		 if( !fin ) {
		 }
		 else
		 {
           fin>>list_length;
		   getline(fin,temp); // trick because of the >> operator stops after what it reads and doesn't 
		                      // goto the next line so this puts that new line character into temp them goes 
		                      //to the next line so that it can be read by the next statement
		
		   for( int i=0; i < list_length; ++i )
		   {     
			 getline(fin,current->text);
	
             getline(fin,current->description);	
		
             fin>>current->number;
			 fin>>current->alphabet;
			 fin>>current->alphabet_case;
			 fin>>current->ascii;
			 getline(fin,temp);// trick because of the >> operator stops after what it reads and doesn't 
		                      // goto the next line so this puts that new line character into temp them goes 
		                      //to the next line so that it can be read by the next statement
		
			 password_list->push_back( *current );
		   }
		 }
     
		 fin.close();
		}

	private:
		void gen_password(void)
		{
		 char current = '*';
 
		  for( int i=0; i < length->Value; ++i )
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


	private: System::Windows::Forms::Label *  label2;

	private: System::Windows::Forms::Label *  label3;


	



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container * components;

	private: System::Windows::Forms::CheckBox *  alphabet;
	private: System::Windows::Forms::CheckBox *  alphabet_case;
	private: System::Windows::Forms::CheckBox *  numbers;


	private: System::Windows::Forms::StatusBar *  statusbar;
	private: System::Windows::Forms::Button *  generate_button;



	private: System::Windows::Forms::CheckBox *  ascii;
	private: System::Windows::Forms::NumericUpDown *  length;
	private: System::Windows::Forms::CheckBox *  save_password;
	private: System::Windows::Forms::Label *  description_text;



	private: System::Windows::Forms::TextBox *  description;



		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->description_text = new System::Windows::Forms::Label();
			this->description = new System::Windows::Forms::TextBox();
			this->label2 = new System::Windows::Forms::Label();
			this->label3 = new System::Windows::Forms::Label();
			this->alphabet = new System::Windows::Forms::CheckBox();
			this->alphabet_case = new System::Windows::Forms::CheckBox();
			this->numbers = new System::Windows::Forms::CheckBox();
			this->statusbar = new System::Windows::Forms::StatusBar();
			this->generate_button = new System::Windows::Forms::Button();
			this->ascii = new System::Windows::Forms::CheckBox();
			this->length = new System::Windows::Forms::NumericUpDown();
			this->save_password = new System::Windows::Forms::CheckBox();
			this->mainMenu1 = new System::Windows::Forms::MainMenu();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->save_menuitem = new System::Windows::Forms::MenuItem();
			this->edit_password_menuitem = new System::Windows::Forms::MenuItem();
			this->exit_menuitem = new System::Windows::Forms::MenuItem();
			this->menuItem4 = new System::Windows::Forms::MenuItem();
			this->menuItem5 = new System::Windows::Forms::MenuItem();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->length))->BeginInit();
			this->SuspendLayout();
			// 
			// description_text
			// 
			this->description_text->Enabled = false;
			this->description_text->Location = System::Drawing::Point(16, 80);
			this->description_text->Name = S"description_text";
			this->description_text->Size = System::Drawing::Size(72, 23);
			this->description_text->TabIndex = 0;
			this->description_text->Text = S" Description";
			// 
			// description
			// 
			this->description->Enabled = false;
			this->description->Location = System::Drawing::Point(96, 80);
			this->description->Name = S"description";
			this->description->Size = System::Drawing::Size(408, 20);
			this->description->TabIndex = 1;
			this->description->Text = S"";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(16, 112);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(120, 23);
			this->label2->TabIndex = 2;
			this->label2->Text = S"Number of Characters";
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(8, 8);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(176, 23);
			this->label3->TabIndex = 4;
			this->label3->Text = S"Options for Generated Password";
			// 
			// alphabet
			// 
			this->alphabet->Location = System::Drawing::Point(32, 144);
			this->alphabet->Name = S"alphabet";
			this->alphabet->Size = System::Drawing::Size(88, 24);
			this->alphabet->TabIndex = 6;
			this->alphabet->Text = S"Alphabet";
			this->alphabet->CheckedChanged += new System::EventHandler(this, &random_password_generator::Form1::alphabet_CheckedChanged);
			// 
			// alphabet_case
			// 
			this->alphabet_case->Enabled = false;
			this->alphabet_case->Location = System::Drawing::Point(128, 144);
			this->alphabet_case->Name = S"alphabet_case";
			this->alphabet_case->Size = System::Drawing::Size(96, 24);
			this->alphabet_case->TabIndex = 7;
			this->alphabet_case->Text = S"case sensitive";
			this->alphabet_case->CheckedChanged += new System::EventHandler(this, &random_password_generator::Form1::alphabet_case_CheckedChanged);
			// 
			// numbers
			// 
			this->numbers->Location = System::Drawing::Point(32, 176);
			this->numbers->Name = S"numbers";
			this->numbers->Size = System::Drawing::Size(120, 24);
			this->numbers->TabIndex = 8;
			this->numbers->Text = S"Numbers";
			this->numbers->CheckedChanged += new System::EventHandler(this, &random_password_generator::Form1::numbers_CheckedChanged);
			// 
			// statusbar
			// 
			this->statusbar->Location = System::Drawing::Point(0, 244);
			this->statusbar->Name = S"statusbar";
			this->statusbar->Size = System::Drawing::Size(552, 22);
			this->statusbar->TabIndex = 11;
			// 
			// generate_button
			// 
			this->generate_button->Location = System::Drawing::Point(144, 208);
			this->generate_button->Name = S"generate_button";
			this->generate_button->Size = System::Drawing::Size(232, 24);
			this->generate_button->TabIndex = 12;
			this->generate_button->Text = S"generate";
			this->generate_button->Click += new System::EventHandler(this, &random_password_generator::Form1::generate_button_Click);
			// 
			// ascii
			// 
			this->ascii->Location = System::Drawing::Point(184, 176);
			this->ascii->Name = S"ascii";
			this->ascii->Size = System::Drawing::Size(296, 16);
			this->ascii->TabIndex = 15;
			this->ascii->Text = S"Any ASCII Character (includes numbers and alphabet)";
			this->ascii->CheckedChanged += new System::EventHandler(this, &random_password_generator::Form1::ascii_CheckedChanged);
			// 
			// length
			// 
			this->length->Location = System::Drawing::Point(136, 112);
			System::Int32 __mcTemp__1[] = new System::Int32[4];
			__mcTemp__1[0] = 600;
			__mcTemp__1[1] = 0;
			__mcTemp__1[2] = 0;
			__mcTemp__1[3] = 0;
			this->length->Maximum = System::Decimal(__mcTemp__1);
			this->length->Name = S"length";
			this->length->Size = System::Drawing::Size(136, 20);
			this->length->TabIndex = 16;
			// 
			// save_password
			// 
			this->save_password->Location = System::Drawing::Point(16, 48);
			this->save_password->Name = S"save_password";
			this->save_password->Size = System::Drawing::Size(192, 24);
			this->save_password->TabIndex = 17;
			this->save_password->Text = S"Save to password list";
			this->save_password->CheckedChanged += new System::EventHandler(this, &random_password_generator::Form1::save_password_CheckedChanged);
			// 
			// mainMenu1
			// 
			System::Windows::Forms::MenuItem* __mcTemp__2[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__2[0] = this->menuItem1;
			__mcTemp__2[1] = this->menuItem4;
			this->mainMenu1->MenuItems->AddRange(__mcTemp__2);
			// 
			// menuItem1
			// 
			this->menuItem1->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__3[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__3[0] = this->save_menuitem;
			__mcTemp__3[1] = this->edit_password_menuitem;
			__mcTemp__3[2] = this->exit_menuitem;
			this->menuItem1->MenuItems->AddRange(__mcTemp__3);
			this->menuItem1->Text = S"File";
			// 
			// save_menuitem
			// 
			this->save_menuitem->Index = 0;
			this->save_menuitem->Text = S"Save";
			this->save_menuitem->Click += new System::EventHandler(this, &random_password_generator::Form1::save_menuitem_Click);
			// 
			// edit_password_menuitem
			// 
			this->edit_password_menuitem->Index = 1;
			this->edit_password_menuitem->Text = S"Edit Passwords";
			this->edit_password_menuitem->Click += new System::EventHandler(this, &random_password_generator::Form1::edit_password_menuitem_Click);
			// 
			// exit_menuitem
			// 
			this->exit_menuitem->Index = 2;
			this->exit_menuitem->Text = S"Exit";
			this->exit_menuitem->Click += new System::EventHandler(this, &random_password_generator::Form1::exit_menuitem_Click);
			// 
			// menuItem4
			// 
			this->menuItem4->Index = 1;
			System::Windows::Forms::MenuItem* __mcTemp__4[] = new System::Windows::Forms::MenuItem*[1];
			__mcTemp__4[0] = this->menuItem5;
			this->menuItem4->MenuItems->AddRange(__mcTemp__4);
			this->menuItem4->Text = S"Help";
			// 
			// menuItem5
			// 
			this->menuItem5->Index = 0;
			this->menuItem5->Text = S"About";
			this->menuItem5->Click += new System::EventHandler(this, &random_password_generator::Form1::menuItem5_Click);
			// 
			// Form1
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(552, 266);
			this->ControlBox = false;
			this->Controls->Add(this->save_password);
			this->Controls->Add(this->length);
			this->Controls->Add(this->ascii);
			this->Controls->Add(this->generate_button);
			this->Controls->Add(this->statusbar);
			this->Controls->Add(this->numbers);
			this->Controls->Add(this->alphabet_case);
			this->Controls->Add(this->alphabet);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->description);
			this->Controls->Add(this->description_text);
			this->Menu = this->mainMenu1;
			this->Name = S"Form1";
			this->Text = S"Random Password Generator";
			this->Load += new System::EventHandler(this, &random_password_generator::Form1::Form1_Load);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->length))->EndInit();
			this->ResumeLayout(false);

		}	




private: System::Void generate_button_Click(System::Object *  sender, System::EventArgs *  e)
			 {
			  if( edit_form->changed == true )
			  {
                statusbar->set_Text( "You must save current changes before generating a new password" );
				return;
			  }
			  if( ascii->Checked == false && numbers->Checked == false && alphabet->Checked == false )
			  {
                statusbar->set_Text( "One character type must be chosen" );
			  }
			  else 
			  if( save_password->Checked == true && description->Text->get_Length() == 0 )
			  {
			    statusbar->set_Text( "Passwords must have a description to be added to password list");
			  }
			  else
			  {
			    // no problems generate password in this block
                statusbar->set_Text( "" );
				gen_password();
				
				password_box->password_text->set_Text( password->str().c_str() );
				if( save_password->Checked == true )
				{
				 current->text = password->str();
				 current->description = nac_string_convert( description->Text );
				 current->ascii = ascii->Checked;
				 current->alphabet = alphabet->Checked;
				 current->alphabet_case = alphabet_case->Checked;
				 current->number = numbers->Checked;
				 password_list->push_back( *current );
				 write_password_list();
				 write_html_password_list();
				}
				password->str("");
				password_box->Show();
				
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

private: System::Void save_password_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
		   if( save_password->Checked == true )
		   {
		    statusbar->set_Text( "Password will be saved to password list" );
			description->Enabled = true;
			description_text->Enabled = true;
		   }
		   else
		   {
		    statusbar->set_Text( "Password will not be saved to password list" );
            description->Enabled = false;
			description_text->Enabled = false;
		   }
		 }

private: System::Void Form1_Load(System::Object *  sender, System::EventArgs *  e)
		 {
           load_password_list();
		 }

private: System::Void edit_password_menuitem_Click(System::Object *  sender, System::EventArgs *  e)
		 {			 
			 if( password_list->begin() == password_list->end() )
			 {
               statusbar->set_Text( "No passwords to edit" );
			   return;
			 }
			 edit_form->password_list->clear();
			 for( list<password_type>::iterator marker = password_list->begin(); marker != password_list->end(); ++marker )
			 {
				 edit_form->password_list->push_back( *marker );
			 }
			
			 edit_form->Show();
		 }

private: System::Void save_menuitem_Click(System::Object *  sender, System::EventArgs *  e)
		 {
		  if( password_list->begin() != password_list->end() )
		  { 
			 if( edit_form->changed == true )
		   {
		    edit_form->changed = false;
			password_list->clear();
			for( unsigned int i =0; i < edit_form->password_list->size(); ++i )
			{
              password_list->push_back( edit_form->password_list->at( i ) );
			}
            write_password_list();
			write_html_password_list();
		   }
		   else
		   {
		    write_password_list();
			write_html_password_list();
		   }
		  }
		  else
		  {
            statusbar->set_Text( "No data to save" );
		  }
		 }

private: System::Void exit_menuitem_Click(System::Object *  sender, System::EventArgs *  e)
		 {
		  if( password_list->begin() != password_list->end() )
		  {
			 if( edit_form->changed == true )
		   {
		    edit_form->changed = false;
			password_list->clear();
			for( unsigned int i =0; i < edit_form->password_list->size(); ++i )
			{
              password_list->push_back( edit_form->password_list->at( i ) );
			}
            write_password_list();
			write_html_password_list();
		   }
		   else
		   {
		    write_password_list();
			write_html_password_list();
		   }
		  }
		     // pops up a message box       
		   int x = MessageBox::Show(S"Exit Random Password Generator ?", S"", MessageBoxButtons::YesNo);
           // if the user clicks no the while loop ends and the user can go on with the rest of the program
           
		   // if the user clicks yes Close everything down.
		   if( x == DialogResult::Yes)  Application::Exit();
		 }

private: System::Void menuItem5_Click(System::Object *  sender, System::EventArgs *  e)
		 {
		   about_form->Show();
		 }

};
}


