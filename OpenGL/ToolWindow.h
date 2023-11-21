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
		static bool RenderRedChannel;
		static bool RenderGreenChannel;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	public:
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::TrackBar^ trackBar2;
	private: System::Windows::Forms::TrackBar^ trackBar3;
	private: System::Windows::Forms::TrackBar^ trackBar4;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ SpecStrength;
	private: System::Windows::Forms::Label^ SpecColor;
	private: System::Windows::Forms::Label^ RLabel;
	private: System::Windows::Forms::Label^ GLabel;
	private: System::Windows::Forms::Label^ BLabel;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
		   static bool RenderBlueChannel;

		ToolWindow(void)
		{
			InitializeComponent();
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
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar3 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar4 = (gcnew System::Windows::Forms::TrackBar());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SpecStrength = (gcnew System::Windows::Forms::Label());
			this->SpecColor = (gcnew System::Windows::Forms::Label());
			this->RLabel = (gcnew System::Windows::Forms::Label());
			this->GLabel = (gcnew System::Windows::Forms::Label());
			this->BLabel = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar4))->BeginInit();
			this->SuspendLayout();
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton1->Location = System::Drawing::Point(34, 12);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(88, 17);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Move Light";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton2->Location = System::Drawing::Point(34, 258);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(120, 17);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Color by Position";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton3->Location = System::Drawing::Point(34, 316);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(154, 17);
			this->radioButton3->TabIndex = 2;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Move Cubes to Sphere";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(171, 66);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(254, 45);
			this->trackBar1->TabIndex = 3;
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(171, 108);
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(254, 45);
			this->trackBar2->TabIndex = 4;
			// 
			// trackBar3
			// 
			this->trackBar3->Location = System::Drawing::Point(171, 151);
			this->trackBar3->Name = L"trackBar3";
			this->trackBar3->Size = System::Drawing::Size(254, 45);
			this->trackBar3->TabIndex = 5;
			// 
			// trackBar4
			// 
			this->trackBar4->Location = System::Drawing::Point(171, 202);
			this->trackBar4->Name = L"trackBar4";
			this->trackBar4->Size = System::Drawing::Size(254, 45);
			this->trackBar4->TabIndex = 6;
			// 
			// button1
			// 
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button1->Location = System::Drawing::Point(47, 35);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(121, 23);
			this->button1->TabIndex = 7;
			this->button1->Text = L"Reset Light Position";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button2->Location = System::Drawing::Point(47, 282);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(121, 23);
			this->button2->TabIndex = 8;
			this->button2->Text = L"Reset Teapot Position";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// SpecStrength
			// 
			this->SpecStrength->AutoSize = true;
			this->SpecStrength->Location = System::Drawing::Point(47, 66);
			this->SpecStrength->Name = L"SpecStrength";
			this->SpecStrength->Size = System::Drawing::Size(92, 13);
			this->SpecStrength->TabIndex = 9;
			this->SpecStrength->Text = L"Specular Strength";
			// 
			// SpecColor
			// 
			this->SpecColor->AutoSize = true;
			this->SpecColor->Location = System::Drawing::Point(50, 108);
			this->SpecColor->Name = L"SpecColor";
			this->SpecColor->Size = System::Drawing::Size(76, 13);
			this->SpecColor->TabIndex = 10;
			this->SpecColor->Text = L"Specular Color";
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
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(432, 66);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(13, 13);
			this->label6->TabIndex = 14;
			this->label6->Text = L"4";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(432, 108);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(28, 13);
			this->label7->TabIndex = 15;
			this->label7->Text = L"1.00";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(432, 151);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(28, 13);
			this->label8->TabIndex = 16;
			this->label8->Text = L"1.00";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(432, 202);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(28, 13);
			this->label9->TabIndex = 17;
			this->label9->Text = L"1.00";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(485, 359);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->BLabel);
			this->Controls->Add(this->GLabel);
			this->Controls->Add(this->RLabel);
			this->Controls->Add(this->SpecColor);
			this->Controls->Add(this->SpecStrength);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->trackBar4);
			this->Controls->Add(this->trackBar3);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar4))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}

};
}
