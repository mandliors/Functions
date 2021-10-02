#pragma once

#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace LinearRegression {

	public ref class Function
	{
	public:
		Function(String^ label, Color color) : Label(label), DrawColor(color)
		{
			Points = gcnew List<PointF>();
			Visible = false;
		}

		void ClearPoints()
		{
			Points->Clear();
		}

		void AddPoint(const PointF& point)
		{
			Points->Add(point);
		}

		bool Draw(System::Windows::Forms::PaintEventArgs^ e, float height)
		{
			if (!Visible) return true;
			Pen^ pen = gcnew Pen(DrawColor);
			
			for (int i = 0; i < Points->Count - 1; i++)
			{
				if (Points[i + 1].Y <= 0 || Points[i + 1].Y >= height) continue;
				try 
				{
					if (Points[i].Y == Points[i].Y && Points[i + 1].Y == Points[i + 1].Y)
						e->Graphics->DrawLine(pen, Points[i], Points[i + 1]);
					else
						{ i++; continue; }
				}
				catch (Exception^ ex)
				{
					Console::WriteLine("A " + Label + " függvény kirajzolásánál hiba történt (figyeljen az értelmezési tartományra!)");
					this->Visible = false;
					return false;
				}
			}
			return true;
		}

	public:
		String^ Label;
		List<PointF>^ Points;
		Color DrawColor;
		bool Visible;
	};

	public ref class DataForm : public System::Windows::Forms::Form
	{
	public:
		DataForm(List<PointF>^ points, List<Function^>^ functions)
		{
			InitializeComponent();
			
			pointsRefSave = points;
			functionsRefSave = functions;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DataForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ pointsDGV;
	protected:

	private: System::Windows::Forms::DataGridViewTextBoxColumn^ x;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ y;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label1;



	protected:



	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::CheckBox^ sineCB;




	private: System::Windows::Forms::CheckBox^ cosineCB;


	private: System::Windows::Forms::CheckBox^ tangentCB;


	private: System::Windows::Forms::CheckBox^ cotangentCB;


	private: System::Windows::Forms::CheckBox^ logarithmCB;



	private: System::Windows::Forms::CheckBox^ exponentialCB;
	private: System::Windows::Forms::CheckBox^ linearRegressionCB;


	private: System::Windows::Forms::Button^ button1;


		   List<PointF>^ pointsRefSave;
		   List<Function^>^ functionsRefSave;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->pointsDGV = (gcnew System::Windows::Forms::DataGridView());
			this->x = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->y = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->sineCB = (gcnew System::Windows::Forms::CheckBox());
			this->cosineCB = (gcnew System::Windows::Forms::CheckBox());
			this->tangentCB = (gcnew System::Windows::Forms::CheckBox());
			this->cotangentCB = (gcnew System::Windows::Forms::CheckBox());
			this->logarithmCB = (gcnew System::Windows::Forms::CheckBox());
			this->exponentialCB = (gcnew System::Windows::Forms::CheckBox());
			this->linearRegressionCB = (gcnew System::Windows::Forms::CheckBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pointsDGV))->BeginInit();
			this->SuspendLayout();
			// 
			// pointsDGV
			// 
			this->pointsDGV->AllowUserToAddRows = false;
			this->pointsDGV->AllowUserToResizeColumns = false;
			this->pointsDGV->AllowUserToResizeRows = false;
			this->pointsDGV->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->pointsDGV->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->pointsDGV->ColumnHeadersVisible = false;
			this->pointsDGV->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) { this->x, this->y });
			this->pointsDGV->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnEnter;
			this->pointsDGV->GridColor = System::Drawing::SystemColors::ActiveBorder;
			this->pointsDGV->Location = System::Drawing::Point(12, 70);
			this->pointsDGV->Name = L"pointsDGV";
			this->pointsDGV->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->pointsDGV->RowHeadersVisible = false;
			this->pointsDGV->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->pointsDGV->Size = System::Drawing::Size(235, 166);
			this->pointsDGV->TabIndex = 0;
			// 
			// x
			// 
			this->x->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::White;
			this->x->DefaultCellStyle = dataGridViewCellStyle1;
			this->x->HeaderText = L"x";
			this->x->Name = L"x";
			this->x->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			// 
			// y
			// 
			this->y->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::White;
			this->y->DefaultCellStyle = dataGridViewCellStyle2;
			this->y->HeaderText = L"y";
			this->y->Name = L"y";
			this->y->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Location = System::Drawing::Point(12, 50);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(118, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"x";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox2->Location = System::Drawing::Point(129, 50);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(118, 20);
			this->textBox2->TabIndex = 2;
			this->textBox2->Text = L"y";
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(46, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(161, 25);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Pontok megadása";
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(131, 239);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(116, 30);
			this->button2->TabIndex = 5;
			this->button2->Text = L"+";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &DataForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(12, 239);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(116, 30);
			this->button3->TabIndex = 6;
			this->button3->Text = L"-";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &DataForm::button3_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel1->Location = System::Drawing::Point(257, 17);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(2, 252);
			this->panel1->TabIndex = 7;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(303, 15);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(112, 25);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Függvények";
			// 
			// sineCB
			// 
			this->sineCB->AutoSize = true;
			this->sineCB->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sineCB->Location = System::Drawing::Point(270, 61);
			this->sineCB->Name = L"sineCB";
			this->sineCB->Size = System::Drawing::Size(81, 25);
			this->sineCB->TabIndex = 9;
			this->sineCB->Text = L"Szinusz";
			this->sineCB->UseVisualStyleBackColor = true;
			// 
			// cosineCB
			// 
			this->cosineCB->AutoSize = true;
			this->cosineCB->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cosineCB->Location = System::Drawing::Point(270, 83);
			this->cosineCB->Name = L"cosineCB";
			this->cosineCB->Size = System::Drawing::Size(97, 25);
			this->cosineCB->TabIndex = 12;
			this->cosineCB->Text = L"Koszinusz";
			this->cosineCB->UseVisualStyleBackColor = true;
			// 
			// tangentCB
			// 
			this->tangentCB->AutoSize = true;
			this->tangentCB->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tangentCB->Location = System::Drawing::Point(270, 105);
			this->tangentCB->Name = L"tangentCB";
			this->tangentCB->Size = System::Drawing::Size(85, 25);
			this->tangentCB->TabIndex = 15;
			this->tangentCB->Text = L"Tangens";
			this->tangentCB->UseVisualStyleBackColor = true;
			// 
			// cotangentCB
			// 
			this->cotangentCB->AutoSize = true;
			this->cotangentCB->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cotangentCB->Location = System::Drawing::Point(270, 127);
			this->cotangentCB->Name = L"cotangentCB";
			this->cotangentCB->Size = System::Drawing::Size(102, 25);
			this->cotangentCB->TabIndex = 18;
			this->cotangentCB->Text = L"Kotangens";
			this->cotangentCB->UseVisualStyleBackColor = true;
			// 
			// logarithmCB
			// 
			this->logarithmCB->AutoSize = true;
			this->logarithmCB->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->logarithmCB->Location = System::Drawing::Point(270, 149);
			this->logarithmCB->Name = L"logarithmCB";
			this->logarithmCB->Size = System::Drawing::Size(108, 25);
			this->logarithmCB->TabIndex = 21;
			this->logarithmCB->Text = L"Logaritmus";
			this->logarithmCB->UseVisualStyleBackColor = true;
			// 
			// exponentialCB
			// 
			this->exponentialCB->AutoSize = true;
			this->exponentialCB->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->exponentialCB->Location = System::Drawing::Point(270, 171);
			this->exponentialCB->Name = L"exponentialCB";
			this->exponentialCB->Size = System::Drawing::Size(122, 25);
			this->exponentialCB->TabIndex = 24;
			this->exponentialCB->Text = L"Exponenciális";
			this->exponentialCB->UseVisualStyleBackColor = true;
			// 
			// linearRegressionCB
			// 
			this->linearRegressionCB->AutoSize = true;
			this->linearRegressionCB->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->linearRegressionCB->Location = System::Drawing::Point(270, 195);
			this->linearRegressionCB->Name = L"linearRegressionCB";
			this->linearRegressionCB->Size = System::Drawing::Size(158, 25);
			this->linearRegressionCB->TabIndex = 27;
			this->linearRegressionCB->Text = L"Lineáris regresszió";
			this->linearRegressionCB->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(270, 239);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(180, 30);
			this->button1->TabIndex = 28;
			this->button1->Text = L"Oké";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &DataForm::button1_Click);
			// 
			// DataForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(457, 272);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->linearRegressionCB);
			this->Controls->Add(this->exponentialCB);
			this->Controls->Add(this->logarithmCB);
			this->Controls->Add(this->cotangentCB);
			this->Controls->Add(this->tangentCB);
			this->Controls->Add(this->cosineCB);
			this->Controls->Add(this->sineCB);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->pointsDGV);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MaximizeBox = false;
			this->Name = L"DataForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Pontok, függvények megadása";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pointsDGV))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		try
		{
			pointsRefSave->Clear();
			for (int i = 0; i < pointsDGV->RowCount; i++)
			{
				pointsRefSave->Add(PointF(std::stof(msclr::interop::marshal_as<std::string>(static_cast<String^>(pointsDGV->Rows[i]->Cells[0]->Value))),
					std::stof(msclr::interop::marshal_as<std::string>(static_cast<String^>(pointsDGV->Rows[i]->Cells[1]->Value)))));
			}
			functionsRefSave[0]->Visible = sineCB->Checked;
			functionsRefSave[1]->Visible = cosineCB->Checked;
			functionsRefSave[2]->Visible = tangentCB->Checked;
			functionsRefSave[3]->Visible = cotangentCB->Checked;
			functionsRefSave[4]->Visible = logarithmCB->Checked;
			functionsRefSave[5]->Visible = exponentialCB->Checked;
			functionsRefSave[6]->Visible = linearRegressionCB->Checked;
			this->Close();
		}
		catch (Exception^ e)
		{
			System::Windows::Forms::MessageBox::Show("Helytelen adatokat adott meg");
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		pointsDGV->Rows->Add();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (pointsDGV->RowCount == 0) return;
		pointsDGV->Rows->RemoveAt(pointsDGV->RowCount - 1);
	}
};
}
