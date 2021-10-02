#pragma once

#include "DataForm.h"

namespace LinearRegression {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CustomForm
	/// </summary>
	public ref class CustomForm : public System::Windows::Forms::Form
	{
	public:
		CustomForm(List<Function^>^ functions)
		{
			InitializeComponent();

			functionsRefSave = functions;
		}

	protected:
		~CustomForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::DataGridView^ functionsDGV;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^ x;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ y;

	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button2;
		   List<Function^>^ functionsRefSave;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->functionsDGV = (gcnew System::Windows::Forms::DataGridView());
			this->x = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->y = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->functionsDGV))->BeginInit();
			this->SuspendLayout();
			// 
			// functionsDGV
			// 
			this->functionsDGV->AllowUserToAddRows = false;
			this->functionsDGV->AllowUserToResizeColumns = false;
			this->functionsDGV->AllowUserToResizeRows = false;
			this->functionsDGV->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->functionsDGV->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->functionsDGV->ColumnHeadersVisible = false;
			this->functionsDGV->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->x });
			this->functionsDGV->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnEnter;
			this->functionsDGV->GridColor = System::Drawing::SystemColors::ActiveBorder;
			this->functionsDGV->Location = System::Drawing::Point(12, 91);
			this->functionsDGV->Name = L"functionsDGV";
			this->functionsDGV->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->functionsDGV->RowHeadersVisible = false;
			this->functionsDGV->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->functionsDGV->Size = System::Drawing::Size(259, 172);
			this->functionsDGV->TabIndex = 1;
			// 
			// x
			// 
			this->x->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle3->BackColor = System::Drawing::Color::White;
			this->x->DefaultCellStyle = dataGridViewCellStyle3;
			this->x->HeaderText = L"x";
			this->x->Name = L"x";
			this->x->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			// 
			// y
			// 
			this->y->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle4->BackColor = System::Drawing::Color::White;
			this->y->DefaultCellStyle = dataGridViewCellStyle4;
			this->y->HeaderText = L"y";
			this->y->Name = L"y";
			this->y->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Location = System::Drawing::Point(12, 71);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(259, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"Hozzárendelési szabály";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(12, 268);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(40, 40);
			this->button3->TabIndex = 7;
			this->button3->Text = L"-";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &CustomForm::button3_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(54, 268);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(40, 40);
			this->button1->TabIndex = 8;
			this->button1->Text = L"+";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &CustomForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(39, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(203, 25);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Függvények megadása";
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(104, 269);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(167, 39);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Oké";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &CustomForm::button2_Click);
			// 
			// CustomForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(283, 317);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->functionsDGV);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"CustomForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Saját függvények megadása";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &CustomForm::CustomForm_FormClosing);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->functionsDGV))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (functionsDGV->RowCount == 0) return;
		functionsDGV->Rows->RemoveAt(functionsDGV->RowCount - 1);
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		functionsDGV->Rows->Add();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		try
		{
			functionsRefSave->Clear();
			for (int i = 0; i < functionsDGV->RowCount; i++)
			{
				functionsRefSave->Add(gcnew Function(functionsDGV->Rows[i]->Cells[0]->Value->ToString(), Color::Black));
				functionsRefSave[i]->Visible = true;
			}
			this->Hide();
		}
		catch (Exception^ e)
		{
			System::Windows::Forms::MessageBox::Show("Helytelen adatokat adott meg");
		}
	}
private: System::Void CustomForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
{
	e->Cancel = true;
	this->Hide();
}
};
}
