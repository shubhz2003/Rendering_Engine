#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:

		static float trackBar_R;
		static float trackBar_G;
		static float trackBar_B;
		static float trackBar_SpecStrength;
		static bool resetLight_Btn;
		static bool resetTeapot_Btn;
		static bool moveLight_Channel;
		static bool colorByPosition_Channel;
		static bool moveCubesToShpere_Channel;

	private: System::Windows::Forms::RadioButton^ moveLightBtn;
	private: System::Windows::Forms::RadioButton^ colorByPositionBtn;
	private: System::Windows::Forms::RadioButton^ moveCubesToSphereBtn;

	private: System::Windows::Forms::TrackBar^ trackBar_SpecStrength_Component;
	private: System::Windows::Forms::TrackBar^ trackBar_R_Component;
	private: System::Windows::Forms::TrackBar^ trackBar_G_Component;
	private: System::Windows::Forms::TrackBar^ trackBar_B_Component;

	private: System::Windows::Forms::Button^ resetLightPosBtn;
	private: System::Windows::Forms::Button^ resetTeapotPosBtn;

	private: System::Windows::Forms::Label^ SpecStrength_Lbl;
	private: System::Windows::Forms::Label^ SpecColor_Lbl;
	private: System::Windows::Forms::Label^ specStrength_LblVal;
	private: System::Windows::Forms::Label^ RLabel;
	private: System::Windows::Forms::Label^ GLabel;
	private: System::Windows::Forms::Label^ BLabel;

	private: System::Windows::Forms::Label^ r_LblVal;
	private: System::Windows::Forms::Label^ g_LblVal;
	private: System::Windows::Forms::Label^ b_LblVal;

	public:
		ToolWindow(void)
		{
			InitializeComponent();
			trackBar_R = 100.0f;
			trackBar_G = 100.0f;
			trackBar_B = 100.0f;
			trackBar_SpecStrength = 4.0f;
			resetLight_Btn = false;
			resetTeapot_Btn = false;
			moveLight_Channel = moveLightBtn->Checked;
			colorByPosition_Channel = colorByPositionBtn->Checked;
			moveCubesToShpere_Channel = moveCubesToSphereBtn->Checked;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>



		void InitializeComponent(void)
		{
			this->moveLightBtn = (gcnew System::Windows::Forms::RadioButton());
			this->colorByPositionBtn = (gcnew System::Windows::Forms::RadioButton());
			this->moveCubesToSphereBtn = (gcnew System::Windows::Forms::RadioButton());
			this->trackBar_SpecStrength_Component = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_R_Component = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_G_Component = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_B_Component = (gcnew System::Windows::Forms::TrackBar());
			this->resetLightPosBtn = (gcnew System::Windows::Forms::Button());
			this->resetTeapotPosBtn = (gcnew System::Windows::Forms::Button());
			this->SpecStrength_Lbl = (gcnew System::Windows::Forms::Label());
			this->SpecColor_Lbl = (gcnew System::Windows::Forms::Label());
			this->RLabel = (gcnew System::Windows::Forms::Label());
			this->GLabel = (gcnew System::Windows::Forms::Label());
			this->BLabel = (gcnew System::Windows::Forms::Label());
			this->specStrength_LblVal = (gcnew System::Windows::Forms::Label());
			this->r_LblVal = (gcnew System::Windows::Forms::Label());
			this->g_LblVal = (gcnew System::Windows::Forms::Label());
			this->b_LblVal = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_SpecStrength_Component))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_R_Component))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_G_Component))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_B_Component))->BeginInit();
			this->SuspendLayout();
			// 
			// moveLightBtn
			// 
			this->moveLightBtn->AutoSize = true;
			this->moveLightBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->moveLightBtn->Location = System::Drawing::Point(34, 12);
			this->moveLightBtn->Name = L"moveLightBtn";
			this->moveLightBtn->Size = System::Drawing::Size(88, 17);
			this->moveLightBtn->TabIndex = 0;
			this->moveLightBtn->TabStop = true;
			this->moveLightBtn->Text = L"Move Light";
			this->moveLightBtn->UseVisualStyleBackColor = true;
			this->moveLightBtn->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::moveLightBtn_CheckedChanged);
			// 
			// colorByPositionBtn
			// 
			this->colorByPositionBtn->AutoSize = true;
			this->colorByPositionBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->colorByPositionBtn->Location = System::Drawing::Point(34, 258);
			this->colorByPositionBtn->Name = L"colorByPositionBtn";
			this->colorByPositionBtn->Size = System::Drawing::Size(120, 17);
			this->colorByPositionBtn->TabIndex = 1;
			this->colorByPositionBtn->TabStop = true;
			this->colorByPositionBtn->Text = L"Color by Position";
			this->colorByPositionBtn->UseVisualStyleBackColor = true;
			this->colorByPositionBtn->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::colorByPositionBtn_CheckedChanged);
			// 
			// moveCubesToSphereBtn
			// 
			this->moveCubesToSphereBtn->AutoSize = true;
			this->moveCubesToSphereBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->moveCubesToSphereBtn->Location = System::Drawing::Point(34, 316);
			this->moveCubesToSphereBtn->Name = L"moveCubesToSphereBtn";
			this->moveCubesToSphereBtn->Size = System::Drawing::Size(154, 17);
			this->moveCubesToSphereBtn->TabIndex = 2;
			this->moveCubesToSphereBtn->TabStop = true;
			this->moveCubesToSphereBtn->Text = L"Move Cubes to Sphere";
			this->moveCubesToSphereBtn->UseVisualStyleBackColor = true;
			this->moveCubesToSphereBtn->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::moveCubesToSphereBtn_CheckedChanged);
			// 
			// trackBar_SpecStrength_Component
			// 
			this->trackBar_SpecStrength_Component->Location = System::Drawing::Point(171, 66);
			this->trackBar_SpecStrength_Component->Maximum = 128;
			this->trackBar_SpecStrength_Component->Minimum = 1;
			this->trackBar_SpecStrength_Component->Name = L"trackBar_SpecStrength_Component";
			this->trackBar_SpecStrength_Component->Size = System::Drawing::Size(254, 45);
			this->trackBar_SpecStrength_Component->TabIndex = 3;
			this->trackBar_SpecStrength_Component->Value = 4;
			this->trackBar_SpecStrength_Component->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_SpecStrength_Component_Scroll);
			// 
			// trackBar_R_Component
			// 
			this->trackBar_R_Component->Location = System::Drawing::Point(171, 108);
			this->trackBar_R_Component->Maximum = 300;
			this->trackBar_R_Component->Name = L"trackBar_R_Component";
			this->trackBar_R_Component->Size = System::Drawing::Size(254, 45);
			this->trackBar_R_Component->TabIndex = 4;
			this->trackBar_R_Component->Value = 100;
			this->trackBar_R_Component->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_R_Component_Scroll);
			// 
			// trackBar_G_Component
			// 
			this->trackBar_G_Component->Location = System::Drawing::Point(171, 151);
			this->trackBar_G_Component->Maximum = 300;
			this->trackBar_G_Component->Name = L"trackBar_G_Component";
			this->trackBar_G_Component->Size = System::Drawing::Size(254, 45);
			this->trackBar_G_Component->TabIndex = 5;
			this->trackBar_G_Component->Value = 100;
			this->trackBar_G_Component->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_G_Component_Scroll);
			// 
			// trackBar_B_Component
			// 
			this->trackBar_B_Component->Location = System::Drawing::Point(171, 202);
			this->trackBar_B_Component->Maximum = 300;
			this->trackBar_B_Component->Name = L"trackBar_B_Component";
			this->trackBar_B_Component->Size = System::Drawing::Size(254, 45);
			this->trackBar_B_Component->TabIndex = 6;
			this->trackBar_B_Component->Value = 100;
			this->trackBar_B_Component->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_B_Component_Scroll);
			// 
			// resetLightPosBtn
			// 
			this->resetLightPosBtn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->resetLightPosBtn->Location = System::Drawing::Point(47, 35);
			this->resetLightPosBtn->Name = L"resetLightPosBtn";
			this->resetLightPosBtn->Size = System::Drawing::Size(121, 23);
			this->resetLightPosBtn->TabIndex = 7;
			this->resetLightPosBtn->Text = L"Reset Light Position";
			this->resetLightPosBtn->UseVisualStyleBackColor = true;
			this->resetLightPosBtn->Click += gcnew System::EventHandler(this, &ToolWindow::resetLightPosBtn_Click);
			// 
			// resetTeapotPosBtn
			// 
			this->resetTeapotPosBtn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->resetTeapotPosBtn->Location = System::Drawing::Point(47, 282);
			this->resetTeapotPosBtn->Name = L"resetTeapotPosBtn";
			this->resetTeapotPosBtn->Size = System::Drawing::Size(121, 23);
			this->resetTeapotPosBtn->TabIndex = 8;
			this->resetTeapotPosBtn->Text = L"Reset Teapot Position";
			this->resetTeapotPosBtn->UseVisualStyleBackColor = true;
			this->resetTeapotPosBtn->Click += gcnew System::EventHandler(this, &ToolWindow::resetTeapotPosBtn_Click);
			// 
			// SpecStrength_Lbl
			// 
			this->SpecStrength_Lbl->AutoSize = true;
			this->SpecStrength_Lbl->Location = System::Drawing::Point(47, 66);
			this->SpecStrength_Lbl->Name = L"SpecStrength_Lbl";
			this->SpecStrength_Lbl->Size = System::Drawing::Size(92, 13);
			this->SpecStrength_Lbl->TabIndex = 9;
			this->SpecStrength_Lbl->Text = L"Specular Strength";
			// 
			// SpecColor_Lbl
			// 
			this->SpecColor_Lbl->AutoSize = true;
			this->SpecColor_Lbl->Location = System::Drawing::Point(50, 108);
			this->SpecColor_Lbl->Name = L"SpecColor_Lbl";
			this->SpecColor_Lbl->Size = System::Drawing::Size(76, 13);
			this->SpecColor_Lbl->TabIndex = 10;
			this->SpecColor_Lbl->Text = L"Specular Color";
			// 
			// RLabel
			// 
			this->RLabel->AutoSize = true;
			this->RLabel->Location = System::Drawing::Point(139, 108);
			this->RLabel->Name = L"RLabel";
			this->RLabel->Size = System::Drawing::Size(15, 13);
			this->RLabel->TabIndex = 11;
			this->RLabel->Text = L"R";
			// 
			// GLabel
			// 
			this->GLabel->AutoSize = true;
			this->GLabel->Location = System::Drawing::Point(139, 151);
			this->GLabel->Name = L"GLabel";
			this->GLabel->Size = System::Drawing::Size(15, 13);
			this->GLabel->TabIndex = 12;
			this->GLabel->Text = L"G";
			// 
			// BLabel
			// 
			this->BLabel->AutoSize = true;
			this->BLabel->Location = System::Drawing::Point(139, 202);
			this->BLabel->Name = L"BLabel";
			this->BLabel->Size = System::Drawing::Size(14, 13);
			this->BLabel->TabIndex = 13;
			this->BLabel->Text = L"B";
			// 
			// specStrength_LblVal
			// 
			this->specStrength_LblVal->AutoSize = true;
			this->specStrength_LblVal->Location = System::Drawing::Point(432, 66);
			this->specStrength_LblVal->Name = L"specStrength_LblVal";
			this->specStrength_LblVal->Size = System::Drawing::Size(13, 13);
			this->specStrength_LblVal->TabIndex = 14;
			this->specStrength_LblVal->Text = L"4";
			// 
			// r_LblVal
			// 
			this->r_LblVal->AutoSize = true;
			this->r_LblVal->Location = System::Drawing::Point(432, 108);
			this->r_LblVal->Name = L"r_LblVal";
			this->r_LblVal->Size = System::Drawing::Size(28, 13);
			this->r_LblVal->TabIndex = 15;
			this->r_LblVal->Text = L"1.00";
			// 
			// g_LblVal
			// 
			this->g_LblVal->AutoSize = true;
			this->g_LblVal->Location = System::Drawing::Point(432, 151);
			this->g_LblVal->Name = L"g_LblVal";
			this->g_LblVal->Size = System::Drawing::Size(28, 13);
			this->g_LblVal->TabIndex = 16;
			this->g_LblVal->Text = L"1.00";
			// 
			// b_LblVal
			// 
			this->b_LblVal->AutoSize = true;
			this->b_LblVal->Location = System::Drawing::Point(432, 202);
			this->b_LblVal->Name = L"b_LblVal";
			this->b_LblVal->Size = System::Drawing::Size(28, 13);
			this->b_LblVal->TabIndex = 17;
			this->b_LblVal->Text = L"1.00";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(485, 359);
			this->Controls->Add(this->b_LblVal);
			this->Controls->Add(this->g_LblVal);
			this->Controls->Add(this->r_LblVal);
			this->Controls->Add(this->specStrength_LblVal);
			this->Controls->Add(this->BLabel);
			this->Controls->Add(this->GLabel);
			this->Controls->Add(this->RLabel);
			this->Controls->Add(this->SpecColor_Lbl);
			this->Controls->Add(this->SpecStrength_Lbl);
			this->Controls->Add(this->resetTeapotPosBtn);
			this->Controls->Add(this->resetLightPosBtn);
			this->Controls->Add(this->trackBar_B_Component);
			this->Controls->Add(this->trackBar_G_Component);
			this->Controls->Add(this->trackBar_R_Component);
			this->Controls->Add(this->trackBar_SpecStrength_Component);
			this->Controls->Add(this->moveCubesToSphereBtn);
			this->Controls->Add(this->colorByPositionBtn);
			this->Controls->Add(this->moveLightBtn);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_SpecStrength_Component))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_R_Component))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_G_Component))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_B_Component))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void moveLightBtn_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		moveLight_Channel = moveLightBtn->Checked;
	}
	private: System::Void resetLightPosBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		resetLight_Btn = true;
	}

	private: System::Void trackBar_SpecStrength_Component_Scroll(System::Object^ sender, System::EventArgs^ e) {
		trackBar_SpecStrength = trackBar_SpecStrength_Component->Value;
		specStrength_LblVal->Text = (trackBar_SpecStrength).ToString();
	}

	private: System::Void trackBar_R_Component_Scroll(System::Object^ sender, System::EventArgs^ e) {
		trackBar_R = trackBar_R_Component->Value / 100.0f;
		r_LblVal->Text = (trackBar_R).ToString();
	}

	private: System::Void trackBar_G_Component_Scroll(System::Object^ sender, System::EventArgs^ e) {
		trackBar_G = trackBar_G_Component->Value / 100.0f;
		g_LblVal->Text = (trackBar_G).ToString();
	}

	private: System::Void trackBar_B_Component_Scroll(System::Object^ sender, System::EventArgs^ e) {
		trackBar_B = trackBar_B_Component->Value / 100.0f;
		b_LblVal->Text = (trackBar_B).ToString();
	}

	private: System::Void colorByPositionBtn_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		colorByPosition_Channel = colorByPositionBtn->Checked;
	}

	private: System::Void resetTeapotPosBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		resetTeapot_Btn = true;
	}

	private: System::Void moveCubesToSphereBtn_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		moveCubesToShpere_Channel = moveCubesToSphereBtn->Checked;

		trackBar_SpecStrength = 4.0f;
		specStrength_LblVal->Text = (trackBar_SpecStrength).ToString();

		trackBar_R_Component->Value = 100.0f;
		trackBar_R = trackBar_R_Component->Value / 100.0f;
		r_LblVal->Text = (trackBar_R).ToString();

		trackBar_G_Component->Value = 100.0f;
		trackBar_G = trackBar_G_Component->Value / 100.0f;
		g_LblVal->Text = (trackBar_G).ToString();

		trackBar_B_Component->Value = 100.0f;
		trackBar_B = trackBar_B_Component->Value / 100.0f;
		b_LblVal->Text = (trackBar_B).ToString();
	}
};
}
