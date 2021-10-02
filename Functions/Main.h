#pragma once

#define EXPRTK

#ifdef EXPRTK
#include "exprtk.hpp"
#endif

#include "DataForm.h"
#include "CustomForm.h"

#include <string>
#include <msclr/marshal_cppstd.h>

#define GRAPH_MAX_MULTIPLIER 7.0f / 6.0f
#define MOVE_SPEED 3.0f
#define ZOOM_AMOUNT 0.02f
#define RES_AMOUNT 0.0000000001f
#define DOT_RADIUS 0.009f

#define BLACK Color::FromArgb(0, 0, 0)
#define WHITE Color::FromArgb(255, 255, 255)
#define RED Color::FromArgb(255, 0, 0)
#define GREEN Color::FromArgb(0, 255, 0)
#define BLUE Color::FromArgb(0, 0, 255)
#define ORANGE Color::FromArgb(255, 128, 0)
#define YELLOW Color::FromArgb(255, 255, 0)
#define CYAN Color::FromArgb(0, 255, 255)
#define MAGENTA Color::FromArgb(255, 0, 255)

#define DEBUGGING

const float lineCountV = 10000;
const float lineCountH = 10000;
float RES_INV = 0.1f;

#ifdef EXPRTK
std::vector<exprtk::symbol_table<double>> symbolTables;
std::vector<exprtk::expression<double>> expressions;
#endif

namespace LinearRegression {

	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main()
		{
			InitializeComponent();

			m_ValueMax = 10;
			m_GraphMax = m_ValueMax * GRAPH_MAX_MULTIPLIER;
			m_Width = this->ClientSize.Width;
			m_Height = this->ClientSize.Height;

			//Offsets and zoom
			m_ScreenOffset = gcnew PointF(m_Width / 2.0f, m_Height / 2.0f);
			m_UserOffset = gcnew PointF(0, 0);
			m_ZoomLevel = lineCountV / 20.0f;
			m_HorizontalSpeed = 0.0f;
			m_VerticalSpeed = 0.0f;

			//Mapping
			m_Dist = m_Width / lineCountV * m_ZoomLevel;
			m_DistDiff = 1.0f;

			//Drawing stuff
			m_BlackPen = gcnew Pen(Color::FromArgb(20, 20, 20));
			m_GrayPen = gcnew Pen(Color::FromArgb(220, 220, 220));
			m_RedBrush = gcnew SolidBrush(Color::FromArgb(240, 20, 20));
			m_BlackBrush = gcnew SolidBrush(Color::Black);
			m_Font = gcnew System::Drawing::Font("Times New Roman", 10);

			//Timer
			Timer^ timer = gcnew Timer();
			timer->Interval = 8;
			timer->Tick += gcnew EventHandler(this, &Main::OnTimerTick);
			timer->Start();

			//Forms data
			m_Points = gcnew List<PointF>();
			m_LRMin = -1;
			m_LRMax = -1;
			m_LRM = -1;
			m_LRB = -1;
		
			//Functions
			m_Functions = gcnew List<Function^>;
			m_CustomFunctions = gcnew List<Function^>;
			m_Functions->Add(gcnew Function("sin(x)", RED));
			m_Functions->Add(gcnew Function("cos(x)", BLUE));
			m_Functions->Add(gcnew Function("tg(x)", GREEN));
			m_Functions->Add(gcnew Function("ctg(x)", CYAN));
			m_Functions->Add(gcnew Function("log(x)", MAGENTA));
			m_Functions->Add(gcnew Function("exp(x)", ORANGE));
			m_Functions->Add(gcnew Function("lin. reg.", BLACK));

			//Forms
			m_DataForm = gcnew DataForm(m_Points, m_Functions);
			m_CustomForm = gcnew CustomForm(m_CustomFunctions);
			
			UpdateControlsLabel();

			exprtk::symbol_table<double> table;
			double x = -1.0;
			table.add_variable("x", x);
			std::string ex = "log(x)";
			exprtk::expression<double> expr;
			expr.register_symbol_table(table);
			exprtk::parser<double> parser;
			parser.compile(ex, table);
			double a = expr.value();
		}

	private: System::ComponentModel::Container ^components;

	private:
		Pen^ m_BlackPen;
		Pen^ m_GrayPen;
		SolidBrush^ m_RedBrush;
		SolidBrush^ m_BlackBrush;
		System::Drawing::Font^ m_Font;

		float m_ValueMax;
		float m_GraphMax;
		float m_Width;
		float m_Height;
		float m_ZoomLevel;
		PointF^ m_ScreenOffset;
		PointF^ m_UserOffset;
		float m_HorizontalSpeed;
		float m_VerticalSpeed;
		float m_Dist;
		float m_DistDiff;

		List<PointF>^ m_Points;
		float m_LRM;
		float m_LRB;
		float m_LRMin;

		List<Function^>^ m_Functions;
		List<Function^>^ m_CustomFunctions;

		DataForm^ m_DataForm;
		CustomForm^ m_CustomForm;
	private: System::Windows::Forms::Label^ controlsLabel;



		   float m_LRMax;

	protected:
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}

		float GetPositionFromValue(float v)
		{
			return (((v + m_GraphMax) / (m_GraphMax * 2.0f)) * ((float)this->ClientSize.Width));
		}

		std::string& RightTrim(std::string& number, char c)
		{
			uint32_t index;
			for (index = number.length() - 1; index >= 0; index--)
				if (number[index] != c) break;
			number.erase(index + 1, number.length() - index - 1);
			return number;
		}

		void DrawDot(System::Windows::Forms::PaintEventArgs^ e, float x0, float y0, float r, const Color& color)
		{
			PointF mapped = CoordToPixel(x0, y0);
			e->Graphics->FillEllipse(gcnew SolidBrush(color), mapped.X - r * 0.5f, mapped.Y - r * 0.5f, r, r);
			e->Graphics->DrawEllipse(m_BlackPen, mapped.X - r * 0.5f, mapped.Y - r * 0.5f, r, r);
		}
		void DrawLine(System::Windows::Forms::PaintEventArgs^ e, float x0, float y0, float x1, float y1, const Color& color)
		{
			PointF mapped0 = CoordToPixel(x0, y0);
			PointF mapped1 = CoordToPixel(x1, y1);
			e->Graphics->DrawLine(gcnew Pen(color), mapped0.X, mapped0.Y, mapped1.X, mapped1.Y);
		}
		void DrawPixel(System::Windows::Forms::PaintEventArgs^ e, float x, float y, const Color& color)
		{
			PointF mapped = CoordToPixel(x, y);
			e->Graphics->FillEllipse(gcnew SolidBrush(color), mapped.X, mapped.Y, 2.0f, 2.0f);
		}
		PointF CoordToPixel(float x, float y)
		{
			return PointF(m_ScreenOffset->X + m_UserOffset->X + x / m_DistDiff * m_Dist,
								m_ScreenOffset->Y + m_UserOffset->Y - y / m_DistDiff * m_Dist);
		}
		PointF PixelToCoord(float x, float y)
		{
			return PointF((x - m_UserOffset->X - m_ScreenOffset->X) * m_DistDiff / m_Dist,
			               (-y - m_UserOffset->Y + m_ScreenOffset->Y) * m_DistDiff / m_Dist);
		}
		void OpenDataForm()
		{
			m_DataForm->ShowDialog();
			UpdateFunctionPoints();
			Invalidate();
		}
		void OpenCustomForm()
		{ 
			m_CustomForm->ShowDialog();
			UpdateCustomFunctionPoints();
			Invalidate();
		}

		void UpdateFunctionPoints()
		{
			//Clear function points
			for (int i = 0; i < m_Functions->Count; i++)
				m_Functions[i]->ClearPoints();

			//Add points to functions
			for (float x = 0.0f; x < m_Width + RES_INV; x += RES_INV)
			{
				float xPos = PixelToCoord(x, 0).X;
				/*Sine*/ if (m_Functions[0]->Visible) m_Functions[0]->AddPoint(CoordToPixel(xPos, sinf(xPos)));
				/*Cosine*/ if (m_Functions[1]->Visible) m_Functions[1]->AddPoint(CoordToPixel(xPos, cosf(xPos)));
				/*Tangent*/ if (m_Functions[2]->Visible) m_Functions[2]->AddPoint(CoordToPixel(xPos, tanf(xPos)));
				/*Cotangent*/ if (m_Functions[3]->Visible) m_Functions[3]->AddPoint(CoordToPixel(xPos, 1.0f / (tanf(xPos) + 0.00001f)));
				/*Logarithm*/ if (m_Functions[4]->Visible && xPos > 0.0f) m_Functions[4]->AddPoint(CoordToPixel(xPos, logf(xPos)));
				/*Exponential*/ if (m_Functions[5]->Visible) m_Functions[5]->AddPoint(CoordToPixel(xPos, expf(xPos)));
			}
			//Linear regression
			float count = m_Points->Count;
			if (count < 2.0f) m_Functions[6]->Visible = false;
			if (!m_Functions[6]->Visible) return;
			float x = 0, y = 0, xx = 0, xy = 0;
			float min = m_Points[0].X;
			float max = m_Points[0].X;
			for (int i = 0; i < m_Points->Count; i++)
			{
				if (m_Points[i].X < min) min = m_Points[i].X;
				else if (m_Points[i].X > max) max = m_Points[i].X;
				x += m_Points[i].X;
				y += m_Points[i].Y;
				xx += m_Points[i].X * m_Points[i].X;
				xy += m_Points[i].X * m_Points[i].Y;
			}
			x /= count;
			y /= count;
			xx /= count;
			xy /= count;
			float m = (xy - x * y) / (xx - x * x);
			float b = y - m * x;
			m_Functions[6]->AddPoint(CoordToPixel(min - 1.0f, m * (min - 1.0f) + b));
			m_Functions[6]->AddPoint(CoordToPixel(max + 1.0f, m * (max + 1.0f) + b));
		}

		void UpdateCustomFunctionPoints()
		{
#ifdef EXPRTK
			exprtk::parser<double> parser;

			//Setup symbol_tables and expressions
			symbolTables.clear();
			expressions.clear();
			double* xS = new double[m_CustomFunctions->Count];
			for (int i = 0; i < m_CustomFunctions->Count; i++)
			{
				symbolTables.emplace_back();
				symbolTables[i].add_variable("x", xS[i]);
				symbolTables[i].add_constants();
				
				expressions.emplace_back();
				expressions[i].register_symbol_table(symbolTables[i]);
				
				String^ str = m_CustomFunctions[i]->Label;
				std::string func = msclr::interop::marshal_as<std::string>(str);
			
				if (!parser.compile(func, expressions[i]))
				{
					MessageBox::Show("Az egyik megadott függvény hibás (figyljen rá, hogy x-en kívül másik változót ne tartalmazzon!)");
					delete[] xS;
					OpenCustomForm();
					return;
				}
			}

			//Clear function points
			for (int i = 0; i < m_CustomFunctions->Count; i++)
				m_CustomFunctions[i]->ClearPoints();

			//Add points to functions
			for (float x = 0.0f; x < m_Width + RES_INV; x += RES_INV)
			{
				float xPos = PixelToCoord(x, 0).X;
				for (int i = 0; i < m_CustomFunctions->Count; i++)
				{
					xS[i] = xPos;
					m_CustomFunctions[i]->AddPoint(CoordToPixel(xPos, (float)expressions[i].value()));
				}
			}
			delete[] xS;
#endif
		}

#ifdef DEBUGGING
		void Log(const std::string& message)
		{
			Console::WriteLine(gcnew System::String(message.c_str()));
		}
		void Log(float number)
		{
			Console::WriteLine(gcnew System::String(std::to_string(number).c_str()));
		}
		void TraceLog(const std::string& message)
		{
			System::Diagnostics::Trace::WriteLine(gcnew System::String(message.c_str()));
		}
		void TraceLog(float number)
		{
			System::Diagnostics::Trace::WriteLine(gcnew System::String(std::to_string(number).c_str()));
		}
		void Show(const std::string& message)
		{
			System::Windows::Forms::MessageBox::Show(gcnew System::String(message.c_str()));
		}
		void Show(int number)
		{
			System::Windows::Forms::MessageBox::Show(gcnew System::String(std::to_string(number).c_str()));
		}
#endif

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->controlsLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// controlsLabel
			// 
			this->controlsLabel->AutoSize = true;
			this->controlsLabel->BackColor = System::Drawing::Color::Transparent;
			this->controlsLabel->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->controlsLabel->Location = System::Drawing::Point(0, 1);
			this->controlsLabel->Margin = System::Windows::Forms::Padding(0);
			this->controlsLabel->Name = L"controlsLabel";
			this->controlsLabel->Size = System::Drawing::Size(0, 13);
			this->controlsLabel->TabIndex = 4;
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(800, 800);
			this->Controls->Add(this->controlsLabel);
			this->DoubleBuffered = true;
			this->Name = L"Main";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Függvények - BÉTA!";
			this->ResizeEnd += gcnew System::EventHandler(this, &Main::Main_Resize);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Main::Main_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Main::OnKeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Main::OnKeyUp);
			this->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::OnMouseWheel);
			this->Resize += gcnew System::EventHandler(this, &Main::Main_Resize);
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

		void UpdateControlsLabel()
		{
			controlsLabel->Text = gcnew String("[WASD]     - kamera mozgatása\n"
				   							   "[GÖRGÕ] - nagyítás / kicsinyítés\n"
				   							   "[NYILAK]  - koord.rszer. egységének változtatása\n"
				   							   "[TAB]         - pontok, függvények megadása\n"
				   							   "[SPACE]    - saját függvények megadása\n");
			controlsLabel->Text += gcnew String(("egység: " + std::to_string(m_DistDiff)).c_str());
		}

	private: System::Void Main_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
	{
		m_Dist = (uint32_t)m_Width / 2 * 2 / lineCountV * m_ZoomLevel;
		float startV = -lineCountV * m_Dist / m_ZoomLevel * 0.5f; float endV = -startV;
		float startH = -lineCountH * m_Dist / m_ZoomLevel * 0.5f; float endH = -startH;

		//Draw vertical lines
		float yC = -lineCountH / 2 * m_Dist + m_ScreenOffset->Y + m_UserOffset->Y;
		for (float x = startV * m_Dist; x < endV * m_Dist; x += m_Dist)
		{
			float posX = x + m_ScreenOffset->X + m_UserOffset->X;
			if (posX < 0 || posX > m_Width) continue;
			String^ text = gcnew String(RightTrim(RightTrim(std::to_string(x * m_DistDiff), '0'), '.').c_str());
			e->Graphics->DrawLine(m_GrayPen, posX, yC, posX, yC + m_Width * m_ZoomLevel);
		}
		//Draw horizontal lines
		float xC = -lineCountV / 2 * m_Dist + m_ScreenOffset->X + m_UserOffset->X;
		for (float y = startH * m_Dist; y < endH * m_Dist; y += m_Dist)
		{
			float posY = y + m_ScreenOffset->Y + m_UserOffset->Y;
			if (posY < 0 || posY > m_Height) continue;
			String^ text = gcnew String(RightTrim(RightTrim(std::to_string(y * m_DistDiff), '0'), '.').c_str());
			e->Graphics->DrawLine(m_GrayPen, xC, posY, xC + m_Width * m_ZoomLevel, posY);
		}

		DrawLine(e, 0, 1000, 0, -1000, BLACK);
		DrawLine(e, -1000, 0, 1000, 0, BLACK);

		//Draw linear points
		e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::None;
		for (int i = 0; i < m_Points->Count; i++)
			DrawDot(e, m_Points[i].X, m_Points[i].Y, DOT_RADIUS * m_ZoomLevel * m_Width / 600.0f, RED);
		//Draw functions
		for (int i = 0; i < m_Functions->Count; i++)
			if (!m_Functions[i]->Draw(e, m_Height)) OpenDataForm();
		//Draw custom functions
		for (int i = 0; i < m_CustomFunctions->Count; i++)
		{
			if (!m_CustomFunctions[i]->Draw(e, m_Height)) OpenCustomForm();
		}
	}
	private:

		System::Void Main_Resize(System::Object^ sender, System::EventArgs^ e)
		{
			m_Width = ClientSize.Width;
			m_Height = ClientSize.Height;
			m_ScreenOffset->X = m_Width / 2.0f;
			m_ScreenOffset->Y = m_Height / 2.0f;
			UpdateFunctionPoints();
			UpdateCustomFunctionPoints();
			Invalidate();
		}

		System::Void OnMouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
		{
			if (e->Delta > 0)
			{
				m_ZoomLevel += m_ZoomLevel * ZOOM_AMOUNT;
				//RES_INV -= RES_INV * RES_AMOUNT;
				//if (RES_INV < 1.0f) RES_INV = 1.0f;
			}
			else
			{
				m_ZoomLevel -= m_ZoomLevel * ZOOM_AMOUNT;
				//RES_INV += RES_INV * RES_AMOUNT;
				//if (RES_INV > 20.0f) RES_INV = 20.0f;
			}
			UpdateFunctionPoints();
			UpdateCustomFunctionPoints();
			Invalidate();
		}
		
		System::Void OnKeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
		{
			if (e->KeyCode == System::Windows::Forms::Keys::W) m_VerticalSpeed = MOVE_SPEED;
			else if (e->KeyCode == System::Windows::Forms::Keys::S) m_VerticalSpeed = -MOVE_SPEED;
			else if (e->KeyCode == System::Windows::Forms::Keys::A) m_HorizontalSpeed = MOVE_SPEED;
			else if (e->KeyCode == System::Windows::Forms::Keys::D) m_HorizontalSpeed = -MOVE_SPEED;
			else if (e->KeyCode == System::Windows::Forms::Keys::Tab)
			{
				m_HorizontalSpeed = 0.0f;
				m_VerticalSpeed = 0.0f;
				OpenDataForm();
			}
			else if (e->KeyCode == System::Windows::Forms::Keys::Space)
			{
				m_HorizontalSpeed = 0.0f;
				m_VerticalSpeed = 0.0f;
				OpenCustomForm();
			}
		}

		System::Void OnKeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
		{
			if (e->KeyCode == System::Windows::Forms::Keys::W) m_VerticalSpeed = 0;
			else if (e->KeyCode == System::Windows::Forms::Keys::S) m_VerticalSpeed = 0;
			else if (e->KeyCode == System::Windows::Forms::Keys::A) m_HorizontalSpeed = 0;
			else if (e->KeyCode == System::Windows::Forms::Keys::D) m_HorizontalSpeed = 0;
			else if (e->KeyCode == System::Windows::Forms::Keys::Up)
			{
				m_DistDiff *= 0.9f;
				UpdateControlsLabel();
				UpdateFunctionPoints();
				UpdateCustomFunctionPoints();
			}
			else if (e->KeyCode == System::Windows::Forms::Keys::Down)
			{
				m_DistDiff *= 1.1f;
				UpdateControlsLabel();
				UpdateFunctionPoints();
				UpdateCustomFunctionPoints();
			}
			Invalidate();
		}

		System::Void OnTimerTick(System::Object^ sender, System::EventArgs^ e)
		{
			m_UserOffset->X += m_HorizontalSpeed;
			m_UserOffset->Y += m_VerticalSpeed;
			if (m_HorizontalSpeed != 0 || m_VerticalSpeed != 0)
			{
				UpdateFunctionPoints();
				UpdateCustomFunctionPoints();
				Invalidate();
			}
		}
};
}
