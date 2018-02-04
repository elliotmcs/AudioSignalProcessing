#pragma once
#include "stdafx.h"
#include <functional>

namespace CppCLR_WinformsProjekt2 {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	enum filter_types { LP, HP, BP, BR, CMB };
	enum slider_types { CUTOFF1, CUTOFF2, CUTOFF, FALLOFF, DELAY, AMPLIFICATION };

	public ref class DialogForm : public System::Windows::Forms::Form
	{
	public:
		DialogForm(int sample_rate, int num_samples, int filter_type, int *variables) {
			this->variables = variables;
			this->filter_type = filter_type;
			this->sample_rate = sample_rate;
			this->num_samples = num_samples;
			InitializeComponent();
			InitializeControls();
		}
	protected:
		~DialogForm() {
			if (components) {
				delete components;
			}
		}

	private:
		int filter_type;
		int sample_rate;
		int num_samples;
		int tab_index = 0;
		int *variables;


	private: System::Windows::Forms::BindingSource^  bindingSource1;




	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;


	private: System::ComponentModel::IContainer^  components;
	protected:
	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
/// <summary>
/// Erforderliche Methode für die Designerunterstützung.
/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->bindingSource1 = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(137, 248);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 6;
			this->button1->Text = L"OK";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &DialogForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(218, 248);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 7;
			this->button2->Text = L"Cancel";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &DialogForm::button2_Click);
			// 
			// DialogForm
			// 
			this->ClientSize = System::Drawing::Size(294, 273);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"DialogForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->EndInit();
			this->ResumeLayout(false);

		}

		void add_slider(char *name, int max, Point *loc, int slider_type) {
			String ^name_str = gcnew String(name);
			String ^lb_ext = gcnew String("_lb");
			String ^trb_ext = gcnew String("_trb");
			String ^tb_ext = gcnew String("_tb");
			System::Windows::Forms::Label^  label = gcnew Label();
			System::Windows::Forms::TrackBar^  track_bar = gcnew TrackBar();
			System::Windows::Forms::TextBox^  text_box = gcnew TextBox();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(track_bar))->BeginInit();
			this->SuspendLayout();

			label->AutoSize = true;
			label->Location = System::Drawing::Point((*loc).X - 3, (*loc).Y - 16);
			label->Name = String::Concat(name_str, lb_ext);
			label->Size = System::Drawing::Size(88, 13);
			label->TabIndex = this->tab_index++;
			label->Text = gcnew String(name);
			this->Controls->Add(label);



			track_bar->Location = *loc;
			track_bar->Name = String::Concat(name_str, trb_ext);
			track_bar->Size = System::Drawing::Size(143, 45);
			track_bar->TabIndex = this->tab_index++;
			track_bar->Maximum = max;



			text_box->Location = System::Drawing::Point((*loc).X + 96, (*loc).Y - 18);
			text_box->Name = String::Concat(name_str, tb_ext);
			text_box->Size = System::Drawing::Size(51, 20);
			text_box->TabIndex = this->tab_index++;	
			switch (slider_type) {
			case CUTOFF:
				track_bar->Scroll += gcnew EventHandler(this, &DialogForm::cutoff_Scroll);
				text_box->TextChanged += gcnew EventHandler(this, &DialogForm::cutoff_TextChanged);
					break;
			case CUTOFF1:
				track_bar->Scroll += gcnew EventHandler(this, &DialogForm::cutoff1_Scroll);
				text_box->TextChanged += gcnew EventHandler(this, &DialogForm::cutoff1_TextChanged);
				break;
			case CUTOFF2:
				track_bar->Scroll += gcnew EventHandler(this, &DialogForm::cutoff2_Scroll);
				text_box->TextChanged += gcnew EventHandler(this, &DialogForm::cutoff2_TextChanged);
				break;
			case FALLOFF:
				track_bar->Scroll += gcnew EventHandler(this, &DialogForm::falloff_Scroll);
				text_box->TextChanged += gcnew EventHandler(this, &DialogForm::falloff_TextChanged);
				break;
			case DELAY:
				track_bar->Scroll += gcnew EventHandler(this, &DialogForm::delay_Scroll);
				text_box->TextChanged += gcnew EventHandler(this, &DialogForm::delay_TextChanged);
				break;
			case AMPLIFICATION:
				track_bar->Scroll += gcnew EventHandler(this, &DialogForm::amp_Scroll);
				text_box->TextChanged += gcnew EventHandler(this, &DialogForm::amp_TextChanged);
				break;
			}
			this->Controls->Add(text_box);
			this->Controls->Add(track_bar);

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(track_bar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		void InitializeControls(void)
		{
			char str1[] = "Cutoff Frequency";
			char str2[] = "Falloff Width";
			char str4[] = "Cutoff 1 Frequency";
			char str5[] = "Cutoff 2 Frequency";
			char str6[] = "Falloff Width";
			char str7[] = "Delay";
			char str8[] = "Amplification";
			switch (filter_type){
			case LP:
				add_slider(str1, sample_rate / 2, new Point(77, 72), CUTOFF);
				add_slider(str2, num_samples / 10, new Point(77, 155), FALLOFF);
				break;
			case HP:
				add_slider(str1, sample_rate / 2, new Point(77, 72), CUTOFF);
				add_slider(str2, num_samples / 10, new Point(77, 155), FALLOFF);
				break;
			case BP:
				add_slider(str4, sample_rate / 2, new Point(77, 72), CUTOFF1);
				add_slider(str5, sample_rate / 2, new Point(77, 155), CUTOFF2);
				add_slider(str6, num_samples / 10, new Point(77, 238), FALLOFF);
				break;
			case BR:
				add_slider(str4, sample_rate / 2, new Point(77, 72), CUTOFF1);
				add_slider(str5, sample_rate / 2, new Point(77, 155), CUTOFF2);
				add_slider(str6, num_samples / 10, new Point(77, 238), FALLOFF);
				break;
			case CMB:
				add_slider(str7, sample_rate / 2, new Point(77, 72), DELAY);
				add_slider(str8, 100, new Point(77, 155), AMPLIFICATION);
				break;
			}
		}

	private: System::Void cutoff_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = safe_cast<TrackBar^>(this->Controls->Find(gcnew String("Cutoff Frequency_trb"), true)[0]);
		TextBox ^tb = safe_cast<TextBox^>(this->Controls->Find(gcnew String("Cutoff Frequency_tb"), true)[0]);

		this->variables[0] = trb->Value;
		tb->Text = System::Convert::ToString(this->variables[0]);
	}
	private: System::Void cutoff1_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = safe_cast<TrackBar^>(this->Controls->Find(gcnew String("Cutoff 1 Frequency_trb"), true)[0]);
		TextBox ^tb = safe_cast<TextBox^>(this->Controls->Find(gcnew String("Cutoff 1 Frequency_tb"), true)[0]);

		this->variables[0] = trb->Value;
		tb->Text = System::Convert::ToString(this->variables[0]);
	}
	private: System::Void cutoff2_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = safe_cast<TrackBar^>(this->Controls->Find(gcnew String("Cutoff 2 Frequency_trb"), true)[0]);
		TextBox ^tb = safe_cast<TextBox^>(this->Controls->Find(gcnew String("Cutoff 2 Frequency_tb"), true)[0]);

		this->variables[2] = trb->Value;
		tb->Text = System::Convert::ToString(this->variables[2]);
	}
	private: System::Void falloff_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = (TrackBar ^)(this->Controls->Find(gcnew String("Falloff Width_trb"), true)[0]);
		TextBox ^tb = (TextBox ^)(this->Controls->Find(gcnew String("Falloff Width_tb"), true)[0]);

		this->variables[1] = trb->Value;
		tb->Text = System::Convert::ToString(this->variables[1]);
	}
	private: System::Void delay_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = (TrackBar ^)(this->Controls->Find(gcnew String("Delay_trb"), true)[0]);
		TextBox ^tb = (TextBox ^)(this->Controls->Find(gcnew String("Delay_tb"), true)[0]);

		this->variables[0] = trb->Value;
		tb->Text = System::Convert::ToString(this->variables[0]);
	}
	private: System::Void amp_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = (TrackBar ^)(this->Controls->Find(gcnew String("Amplification_trb"), true)[0]);
		TextBox ^tb = (TextBox ^)(this->Controls->Find(gcnew String("Amplification_tb"), true)[0]);

		this->variables[1] = trb->Value;
		tb->Text = System::Convert::ToString(this->variables[1]);
	}
	private: System::Void cutoff_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = (TrackBar ^)(this->Controls->Find(gcnew String("Cutoff Frequency_trb"), true)[0]);
		TextBox ^tb = (TextBox ^)(this->Controls->Find(gcnew String("Cutoff Frequency_tb"), true)[0]);
		int new_cutoff;
		try {
			new_cutoff = Convert::ToInt32(tb->Text);
			if (new_cutoff > trb->Maximum) {
				new_cutoff = trb->Maximum;
				tb->Text = Convert::ToString(new_cutoff);
			}
			this->variables[0] = new_cutoff;
			trb->Value = (this->variables[0] == -1) ? 0 : this->variables[0];
		}
		catch (FormatException ^e) {
			tb->Text = Convert::ToString(this->variables[0]);
		}
	}
	private: System::Void cutoff1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = (TrackBar ^)(this->Controls->Find(gcnew String("Cutoff 1 Frequency_trb"), true)[0]);
		TextBox ^tb = (TextBox ^)(this->Controls->Find(gcnew String("Cutoff 1 Frequency_tb"), true)[0]);
		int new_cutoff;
		try {
			new_cutoff = Convert::ToInt32(tb->Text);
			if (new_cutoff > trb->Maximum) {
				new_cutoff = trb->Maximum;
				tb->Text = Convert::ToString(new_cutoff);
			}
			this->variables[0] = new_cutoff;
			trb->Value = (this->variables[0] == -1) ? 0 : this->variables[0];
		}
		catch (FormatException ^e) {
			tb->Text = Convert::ToString(this->variables[0]);
		}
	}
	private: System::Void cutoff2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = (TrackBar ^)(this->Controls->Find(gcnew String("Cutoff 2 Frequency_trb"), true)[0]);
		TextBox ^tb = (TextBox ^)(this->Controls->Find(gcnew String("Cutoff 2 Frequency_tb"), true)[0]);
		int new_cutoff;
		try {
			new_cutoff = Convert::ToInt32(tb->Text);
			if (new_cutoff > trb->Maximum) {
				new_cutoff = trb->Maximum;
				tb->Text = Convert::ToString(new_cutoff);
			}
			this->variables[2] = new_cutoff;
			trb->Value = (this->variables[2] == -1) ? 0 : this->variables[2];
		}
		catch (FormatException ^e) {
			tb->Text = Convert::ToString(this->variables[2]);
		}
	}
	private: System::Void falloff_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = (TrackBar ^)(this->Controls->Find(gcnew String("Falloff Width_trb"), true)[0]);
		TextBox ^tb = (TextBox ^)(this->Controls->Find(gcnew String("Falloff Width_tb"), true)[0]);
		int new_falloff;
		try {
			new_falloff = Convert::ToInt32(tb->Text);
			if (new_falloff > trb->Maximum) {
				new_falloff = trb->Maximum;
				tb->Text = Convert::ToString(new_falloff);
			}
			this->variables[1] = new_falloff;
			trb->Value = (this->variables[1] == -1) ? 0 : this->variables[1];
		}
		catch (FormatException ^e) {
			tb->Text = Convert::ToString(this->variables[1]);
		}
	}
	private: System::Void delay_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = (TrackBar ^)(this->Controls->Find(gcnew String("Delay_trb"), true)[0]);
		TextBox ^tb = (TextBox ^)(this->Controls->Find(gcnew String("Delay_tb"), true)[0]);
		int new_falloff;
		try {
			new_falloff = Convert::ToInt32(tb->Text);
			if (new_falloff > trb->Maximum) {
				new_falloff = trb->Maximum;
				tb->Text = Convert::ToString(new_falloff);
			}
			this->variables[0] = new_falloff;
			trb->Value = (this->variables[0] == -1) ? 0 : this->variables[0];
		}
		catch (FormatException ^e) {
			tb->Text = Convert::ToString(this->variables[0]);
		}
	}
	private: System::Void amp_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		TrackBar ^trb = (TrackBar ^)(this->Controls->Find(gcnew String("Amplification_trb"), true)[0]);
		TextBox ^tb = (TextBox ^)(this->Controls->Find(gcnew String("Amplification_tb"), true)[0]);
		int new_falloff;
		try {
			new_falloff = Convert::ToInt32(tb->Text);
			if (new_falloff > trb->Maximum) {
				new_falloff = trb->Maximum;
				tb->Text = Convert::ToString(new_falloff);
			}
			this->variables[1] = new_falloff;
			trb->Value = (this->variables[1] == -1) ? 0 : this->variables[1];
		}
		catch (FormatException ^e) {
			tb->Text = Convert::ToString(this->variables[1]);
		}
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
		//delete this;
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->Close();
		//this->Hide();
		//delete this;
	}
	};

}