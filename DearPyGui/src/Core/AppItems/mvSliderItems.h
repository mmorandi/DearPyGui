#pragma once

#include "Core/AppItems/mvTypeBases.h"
#include "mvPythonTranslator.h"
#include <utility>
#include "mvAppItem.h"

#include "Core/mvValueStorage.h"

//-----------------------------------------------------------------------------
// Widget Index
//
//     * mvSliderFloat
//     * mvSliderFloat2
//     * mvSliderFloat3
//     * mvSliderFloat4
//     * mvSliderInt
//     * mvSliderInt2
//     * mvSliderInt3
//     * mvSliderInt4
//
//-----------------------------------------------------------------------------

namespace Marvel {

	//-----------------------------------------------------------------------------
	// mvSliderFloat
	//-----------------------------------------------------------------------------
	class mvSliderFloat : public mvFloatPtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::SliderFloat, "add_slider_float")

		mvSliderFloat(const std::string& name, float default_value, const std::string& dataSource)
			: mvFloatPtrBase(name, default_value, dataSource)
		{
		}

		void draw() override
		{
			pushColorStyles();
			ImGui::PushID(this);

			if (m_vertical)
			{
				if ((float)m_height < 1.0f)
					m_height = 100.f;
				if ((float)m_width < 1.0f)
					m_width = 20.f;

				if (ImGui::VSliderFloat(m_label.c_str(), ImVec2((float)m_width, (float)m_height), m_value, m_min, m_max, m_format.c_str()))
				{

					mvApp::GetApp()->runCallback(m_callback, m_name, m_callbackData);

					// Context Menu
					if (!getPopup().empty())
						ImGui::OpenPopup(getPopup().c_str());
				}

				// Regular Tooltip (simple)
				if (!getTip().empty() && ImGui::IsItemHovered())
					ImGui::SetTooltip("%s", getTip().c_str());
			}
			else
			{
				if (ImGui::SliderFloat(m_label.c_str(), m_value, m_min, m_max, m_format.c_str(), m_flags))
				{

					mvApp::GetApp()->runCallback(m_callback, m_name, m_callbackData);

					// Context Menu
					if (!getPopup().empty())
						ImGui::OpenPopup(getPopup().c_str());
				}

				// Regular Tooltip (simple)
				if (!getTip().empty() && ImGui::IsItemHovered())
					ImGui::SetTooltip("%s", getTip().c_str());
			}

			ImGui::PopID();
			popColorStyles();
		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
			if (PyObject* item = PyDict_GetItemString(dict, "vertical")) m_vertical = ToBool(item);
			if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
			if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));
			PyDict_SetItemString(dict, "vertical", ToPyBool(m_vertical));
			PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
			PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

	private:

		float               m_min = 0.0f;
		float               m_max = 100.0f;
		std::string         m_format = "%.3f";
		bool                m_vertical = false;
		ImGuiInputTextFlags m_flags = 0;

	};

	//-----------------------------------------------------------------------------
	// mvSliderInt
	//-----------------------------------------------------------------------------
	class mvSliderInt : public mvIntPtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::SliderInt, "add_slider_int")

		mvSliderInt(const std::string& name, int default_value, const std::string& dataSource)
			: mvIntPtrBase(name, default_value, dataSource)
		{
		}

		void draw() override
		{
			pushColorStyles();
			ImGui::PushID(this);

			if (m_vertical)
			{
				if ((float)m_height < 1.0f)
					m_height = 100.f;
				if ((float)m_width < 1.0f)
					m_width = 20.f;

				if (ImGui::VSliderInt(m_label.c_str(), ImVec2((float)m_width, (float)m_height), m_value, m_min, m_max, m_format.c_str()))
				{

					mvApp::GetApp()->runCallback(m_callback, m_name, m_callbackData);

					// Context Menu
					if (!getPopup().empty())
						ImGui::OpenPopup(getPopup().c_str());
				}

				// Regular Tooltip (simple)
				if (!getTip().empty() && ImGui::IsItemHovered())
					ImGui::SetTooltip("%s", getTip().c_str());
			}
			else
			{
				if (ImGui::SliderInt(m_label.c_str(), m_value, m_min, m_max, m_format.c_str(), m_flags))
				{
					mvApp::GetApp()->runCallback(m_callback, m_name, m_callbackData);

					// Context Menu
					if (!getPopup().empty())
						ImGui::OpenPopup(getPopup().c_str());
				}

				// Regular Tooltip (simple)
				if (!getTip().empty() && ImGui::IsItemHovered())
					ImGui::SetTooltip("%s", getTip().c_str());
			}

			ImGui::PopID();
			popColorStyles();
		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
			if (PyObject* item = PyDict_GetItemString(dict, "vertical")) m_vertical = ToBool(item);
			if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
			if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));
			PyDict_SetItemString(dict, "vertical", ToPyBool(m_vertical));
			PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
			PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

	private:

		int                 m_min = 0;
		int                 m_max = 100;
		std::string         m_format = "%d";
		bool                m_vertical = false;
		ImGuiInputTextFlags m_flags = 0;

	};

	//-----------------------------------------------------------------------------
	// mvSliderFloat2
	//-----------------------------------------------------------------------------
	class mvSliderFloat2 : public mvFloat2PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::SliderFloat2, "add_slider_float2")

		mvSliderFloat2(const std::string& name, float* default_value, const std::string& dataSource)
			: mvFloat2PtrBase(name, default_value, dataSource)
		{
		}

		void draw() override
		{
			pushColorStyles();
			ImGui::PushID(this);

			if (ImGui::SliderFloat2(m_label.c_str(), m_value, m_min, m_max, m_format.c_str(), m_flags))
			{

				mvApp::GetApp()->runCallback(m_callback, m_name, m_callbackData);

				// Context Menu
				if (!getPopup().empty())
					ImGui::OpenPopup(getPopup().c_str());
			}

			// Regular Tooltip (simple)
			if (!getTip().empty() && ImGui::IsItemHovered())
				ImGui::SetTooltip("%s", getTip().c_str());

			ImGui::PopID();
			popColorStyles();
		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
			if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
			if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));
			PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
			PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

	private:

		float               m_min = 0.0f;
		float               m_max = 100.0f;
		std::string         m_format = "%.3f";
		ImGuiInputTextFlags m_flags = 0;

	};

	//-----------------------------------------------------------------------------
	// mvSliderFloat3
	//-----------------------------------------------------------------------------
	class mvSliderFloat3 : public mvFloat3PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::SliderFloat3, "add_slider_float3")

		mvSliderFloat3(const std::string& name, float* default_value, const std::string& dataSource)
			: mvFloat3PtrBase(name, default_value, dataSource)
		{
		}

		void draw() override
		{
			pushColorStyles();
			ImGui::PushID(this);

			if (ImGui::SliderFloat3(m_label.c_str(), m_value, m_min, m_max, m_format.c_str(), m_flags))
			{

				mvApp::GetApp()->runCallback(m_callback, m_name, m_callbackData);

				// Context Menu
				if (!getPopup().empty())
					ImGui::OpenPopup(getPopup().c_str());
			}

			// Regular Tooltip (simple)
			if (!getTip().empty() && ImGui::IsItemHovered())
				ImGui::SetTooltip("%s", getTip().c_str());

			ImGui::PopID();
			popColorStyles();
		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
			if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
			if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));
			PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
			PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

	private:

		float               m_min = 0.0f;
		float               m_max = 100.0f;
		std::string         m_format = "%.3f";
		ImGuiInputTextFlags m_flags = 0;

	};

	//-----------------------------------------------------------------------------
	// mvSliderFloat4
	//-----------------------------------------------------------------------------
	class mvSliderFloat4 : public mvFloat4PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::SliderFloat4, "add_slider_float4")

		mvSliderFloat4(const std::string& name, float* default_value, const std::string& dataSource)
			: mvFloat4PtrBase(name, default_value, dataSource)
		{
		}

		void draw() override
		{
			pushColorStyles();
			ImGui::PushID(this);

			if (ImGui::SliderFloat4(m_label.c_str(), m_value, m_min, m_max, m_format.c_str(), m_flags))
			{

				mvApp::GetApp()->runCallback(m_callback, m_name, m_callbackData);

				// Context Menu
				if (!getPopup().empty())
					ImGui::OpenPopup(getPopup().c_str());
			}

			// Regular Tooltip (simple)
			if (!getTip().empty() && ImGui::IsItemHovered())
				ImGui::SetTooltip("%s", getTip().c_str());

			ImGui::PopID();
			popColorStyles();
		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
			if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
			if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));
			PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
			PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

	private:

		float               m_min = 0.0f;
		float               m_max = 100.0f;
		std::string         m_format = "%.3f";
		ImGuiInputTextFlags m_flags = 0;

	};

	//-----------------------------------------------------------------------------
	// mvSliderInt2
	//-----------------------------------------------------------------------------
	class mvSliderInt2 : public mvInt2PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::SliderInt2, "add_slider_int2")

		mvSliderInt2(const std::string& name, int* default_value, const std::string& dataSource)
			: mvInt2PtrBase(name, default_value, dataSource)
		{
		}

		void draw() override
		{
			pushColorStyles();
			ImGui::PushID(this);

			if (ImGui::SliderInt2(m_label.c_str(), m_value, m_min, m_max, m_format.c_str(), m_flags))
			{

				mvApp::GetApp()->runCallback(m_callback, m_name, m_callbackData);

				// Context Menu
				if (!getPopup().empty())
					ImGui::OpenPopup(getPopup().c_str());
			}

			// Regular Tooltip (simple)
			if (!getTip().empty() && ImGui::IsItemHovered())
				ImGui::SetTooltip("%s", getTip().c_str());

			ImGui::PopID();
			popColorStyles();
		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
			if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
			if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));
			PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
			PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

	private:

		int                 m_min = 0;
		int                 m_max = 100;
		std::string         m_format = "%d";
		ImGuiInputTextFlags m_flags = 0;

	};

	//-----------------------------------------------------------------------------
	// mvSliderInt3
	//-----------------------------------------------------------------------------
	class mvSliderInt3 : public mvInt3PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::SliderInt3, "add_slider_int3")

		mvSliderInt3(const std::string& name, int* default_value, const std::string& dataSource)
			: mvInt3PtrBase(name, default_value, dataSource)
		{
		}

		void draw() override
		{
			pushColorStyles();
			ImGui::PushID(this);

			if (ImGui::SliderInt3(m_label.c_str(), m_value, m_min, m_max, m_format.c_str(), m_flags))
			{

				mvApp::GetApp()->runCallback(m_callback, m_name, m_callbackData);

				// Context Menu
				if (!getPopup().empty())
					ImGui::OpenPopup(getPopup().c_str());
			}

			// Regular Tooltip (simple)
			if (!getTip().empty() && ImGui::IsItemHovered())
				ImGui::SetTooltip("%s", getTip().c_str());

			ImGui::PopID();
			popColorStyles();
		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
			if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
			if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));
			PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
			PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

	private:

		int                 m_min = 0;
		int                 m_max = 100;
		std::string         m_format = "%d";
		ImGuiInputTextFlags m_flags = 0;

	};

	//-----------------------------------------------------------------------------
	// mvSliderInt4
	//-----------------------------------------------------------------------------
	class mvSliderInt4 : public mvInt4PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::SliderInt4, "add_slider_int4")

		mvSliderInt4(const std::string& name, int* default_value, const std::string& dataSource)
			: mvInt4PtrBase(name, default_value, dataSource)
		{
		}

		void draw() override
		{
			pushColorStyles();
			ImGui::PushID(this);

			if (ImGui::SliderInt4(m_label.c_str(), m_value, m_min, m_max, m_format.c_str(), m_flags))
			{

				mvApp::GetApp()->runCallback(m_callback, m_name, m_callbackData);

				// Context Menu
				if (!getPopup().empty())
					ImGui::OpenPopup(getPopup().c_str());
			}

			// Regular Tooltip (simple)
			if (!getTip().empty() && ImGui::IsItemHovered())
				ImGui::SetTooltip("%s", getTip().c_str());

			ImGui::PopID();
			popColorStyles();
		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
			if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
			if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));
			PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
			PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);

		}

	private:

		int                 m_min = 0;
		int                 m_max = 100;
		std::string         m_format = "%d";
		ImGuiInputTextFlags m_flags = 0;

	};

}