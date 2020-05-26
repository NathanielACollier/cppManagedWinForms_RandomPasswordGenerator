#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace random_password_generator
{
	/// <summary> 
	/// Summary for password_display
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class password_display : public System::Windows::Forms::Form
	{
	public: 
		password_display(void)
		{
			InitializeComponent();
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
	public: System::Windows::Forms::TextBox *  password_text;
	private: System::Windows::Forms::Button *  ok_button;




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
			this->password_text = new System::Windows::Forms::TextBox();
			this->ok_button = new System::Windows::Forms::Button();
			this->SuspendLayout();
			// 
			// password_text
			// 
			this->password_text->Location = System::Drawing::Point(24, 16);
			this->password_text->MaxLength = 100;
			this->password_text->Multiline = true;
			this->password_text->Name = S"password_text";
			this->password_text->Size = System::Drawing::Size(752, 104);
			this->password_text->TabIndex = 0;
			this->password_text->Text = S"";
			// 
			// ok_button
			// 
			this->ok_button->Location = System::Drawing::Point(648, 136);
			this->ok_button->Name = S"ok_button";
			this->ok_button->Size = System::Drawing::Size(96, 24);
			this->ok_button->TabIndex = 1;
			this->ok_button->Text = S"ok";
			this->ok_button->Click += new System::EventHandler(this, &random_password_generator::password_display::ok_button_Click);
			// 
			// password_display
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(792, 166);
			this->ControlBox = false;
			this->Controls->Add(this->ok_button);
			this->Controls->Add(this->password_text);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = S"password_display";
			this->Text = S"Your Password is";
			this->ResumeLayout(false);

		}		
	private: System::Void ok_button_Click(System::Object *  sender, System::EventArgs *  e)
			 {
			  this->Hide();
			 }

	};
}