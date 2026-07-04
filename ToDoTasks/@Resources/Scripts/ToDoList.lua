local fields = { "Hdn", "Clr", "Cpd", "Ttl", "Tme", "Nte" }
local title_extra_height = 18
local row_h = 64
local row_s = 32
local list_slot_h = 82
local note_h = 28
local note_line_h = 16
local note_wrap_units = 18
local note_max_lines = 16
local note_max_meters = 16
local header_y = 48

local function settings_path()
	return SKIN:GetVariable("CURRENTSKINSETTINGS", "")
end

local function key(slot, field)
	return string.format("EVENT___________%d.%s", slot, field)
end

local function value(slot, field)
	return SKIN:GetVariable(key(slot, field), field == "Nte" and "" or "0")
end

local function write(slot, field, val)
	SKIN:Bang("!WriteKeyValue", "Variables", key(slot, field), val or "", settings_path())
end

local function clamp(value, min_value, max_value)
	if value < min_value then
		return min_value
	end
	if value > max_value then
		return max_value
	end
	return value
end

local function fmt(value)
	local rounded = math.floor(value + 0.5)
	if math.abs(value - rounded) < 0.001 then
		return tostring(rounded)
	end
	return (string.format("%.3f", value):gsub("0+$", ""):gsub("%.$", ""))
end

local function number_var(name, default)
	return tonumber(SKIN:GetVariable(name, tostring(default))) or default
end

local function set_var(name, value)
	SKIN:Bang("!SetVariable", name, fmt(value))
end

local function set_note_line(slot, line, value)
	local meter = line == 0 and ("Nte" .. slot) or ("Nte" .. slot .. "L" .. line)
	SKIN:Bang("!SetOption", meter, "Text", value or "")
end

local function update_view()
	SKIN:Bang("!UpdateMeasure", "Ms.Page.01")
	SKIN:Bang("!UpdateMeasure", "Ms.Page.02")
	SKIN:Bang("!Update")
	SKIN:Bang("!Redraw")
end

local function trim(text)
	return (text or ""):gsub("^%s+", ""):gsub("%s+$", "")
end

local function has_note(slot)
	return trim(value(slot, "Nte")) ~= ""
end

local function clean_literal_input_notes()
	for slot = 0, 7 do
		if value(slot, "Nte") == "$UserInput$" then
			write(slot, "Nte", "")
			SKIN:Bang("!SetVariable", key(slot, "Nte"), "")
		end
	end
end

local function text_char(text, i)
	local byte = text:byte(i)
	if not byte then
		return nil
	end
	if byte < 128 then
		local char = string.char(byte)
		if char:match("%s") then
			return char, 0.5, i + 1
		elseif char:match("%p") then
			return char, 0.7, i + 1
		end
		return char, 1.05, i + 1
	elseif byte < 224 then
		return text:sub(i, i + 1), 2.35, i + 2
	elseif byte < 240 then
		return text:sub(i, i + 2), 2.35, i + 3
	end
	return text:sub(i, i + 3), 2.35, i + 4
end

local function text_token(text, i)
	local char, units_for_char, next_i = text_char(text, i)
	if text:byte(i) < 128 and char:match("%w") then
		while next_i <= #text do
			local next_byte = text:byte(next_i)
			if next_byte >= 128 then
				break
			end
			local next_char, next_units, token_next_i = text_char(text, next_i)
			if not next_char:match("%w") then
				break
			end
			char = char .. next_char
			units_for_char = units_for_char + next_units
			next_i = token_next_i
		end
	end
	return char, units_for_char, next_i
end

local function wrap_lines(text, limit)
	text = text or ""
	if limit <= 0 then
		return { text }
	end

	local lines = {}
	local line = ""
	local line_units = 0
	local i = 1
	while i <= #text do
		local byte = text:byte(i)
		if byte == 10 or byte == 13 then
			table.insert(lines, line)
			line = ""
			line_units = 0
			i = i + 1
		else
			local char, units_for_char, next_i = text_token(text, i)
			if line ~= "" and line_units + units_for_char > limit then
				table.insert(lines, line)
				line = char
				line_units = units_for_char
			else
				line = line .. char
				line_units = line_units + units_for_char
			end
			i = next_i
		end
	end
	table.insert(lines, line)
	return lines
end

local function note_width()
	local note_w = number_var("NoteW", -1)
	if note_w <= 0 then
		note_w = number_var("PW", 4) * 64 - number_var("NoteX", 40) - number_var("NoteRightPad", 28)
	end
	return note_w
end

local function note_limit()
	local note_w = note_width()
	local max_note_w = number_var("PanelW", 320)
	if note_w <= 0 or note_w > max_note_w then
		note_w = 200
	end
	return note_wrap_units * note_w / 80
end

local function note_height(slot, limit)
	local lines = wrap_lines(value(slot, "Nte"), limit)
	return math.max(note_h, math.min(#lines, note_max_lines) * note_line_h + 8)
end

local function sync_layout(requested_index)
	title_extra_height = tonumber(SKIN:GetVariable("TitleExtraH", title_extra_height)) or title_extra_height
	row_h = number_var("RowH", row_h)
	row_s = number_var("RowS", row_s)
	list_slot_h = number_var("ListSlotH", row_h + title_extra_height)
	note_h = number_var("NoteH", note_h)
	note_line_h = number_var("NoteLineH", note_line_h)
	note_wrap_units = number_var("NoteWrapUnits", note_wrap_units)
	note_max_lines = clamp(math.floor(number_var("NoteMaxLines", note_max_lines)), 1, note_max_meters)

	local note_text_limit = note_limit()
	local content_h = 0
	local extras = {}
	local actual_heights = {}
	local row_ys = {}

	for slot = 0, 7 do
		local extra = 0
		if value(slot, "Hdn") ~= "1" then
			extra = title_extra_height
		end

		local anim = clamp(number_var("Nte.Anim" .. slot, 0), 0, 1)
		local note_lines = wrap_lines(value(slot, "Nte"), note_text_limit)
		local note_actual_h = note_height(slot, note_text_limit)
		local actual_h = 0
		if value(slot, "Hdn") ~= "1" then
			actual_h = list_slot_h + note_actual_h * anim
			content_h = content_h + actual_h
		else
			anim = 0
			note_actual_h = 0
			note_lines = {}
		end

		extras[slot] = extra
		actual_heights[slot] = actual_h
		set_var("Nte.Anim" .. slot, anim)
		for line = 0, note_max_lines - 1 do
			set_note_line(slot, line, note_lines[line + 1] or "")
		end
		set_var("Ttl.Extra" .. slot, extra)
		set_var("NoteH.Actual" .. slot, note_actual_h)
		set_var("RowH.Actual" .. slot, actual_h)
	end

	local max_q = math.ceil((content_h + list_slot_h) / row_s)
	local dis_q = number_var("Quantity", 0) * list_slot_h / row_s
	local max_index = math.max(max_q - dis_q, 0)
	local index = clamp(requested_index or number_var("Index", 0), 0, max_index)
	local scroll_offset = index * row_s
	local y = 0

	for slot = 0, 7 do
		local row_y = header_y + y - scroll_offset
		row_ys[slot] = row_y
		set_var("RowY" .. slot, row_y)
		set_var("Nte.Y" .. slot, row_y + 61 + extras[slot])
		set_var("NteEdit.Y" .. slot, row_y + 60 + extras[slot])

		if value(slot, "Hdn") ~= "1" then
			y = y + actual_heights[slot]
		end
	end

	local page_start = 0
	local page_end = 0
	local viewport_top = header_y
	local viewport_bottom = header_y + number_var("Quantity", 0) * list_slot_h
	for slot = 0, 7 do
		if value(slot, "Hdn") ~= "1" then
			local row_top = row_ys[slot]
			local row_bottom = row_top + actual_heights[slot]
			if row_bottom > viewport_top and row_top < viewport_bottom then
				if page_start == 0 then
					page_start = slot + 1
				end
				page_end = slot + 1
			end
		end
	end

	set_var("AddY", header_y + y - scroll_offset)
	set_var("Index", index)
	set_var("MaxQ", max_q)
	set_var("PageStart", page_start)
	set_var("PageEnd", page_end)
	set_var("ScrollOffset", scroll_offset)
end

local function restore_note()
	local slot = tonumber(SKIN:GetVariable("Nte.Resume", "-1"))
	if not slot or slot < 0 or slot > 7 then
		return
	end

	SKIN:Bang("!WriteKeyValue", "Variables", "Nte.Resume", "-1", settings_path())
	if not has_note(slot) then
		return
	end

	SKIN:Bang("!SetVariable", "Nte.Open" .. slot, "1")
	SKIN:Bang("!SetVariable", "Nte.Anim" .. slot, "1")
end

function Initialize()
	clean_literal_input_notes()
	restore_note()
	sync_layout()
end

function Update()
	sync_layout()
	return 0
end

function Scroll(delta)
	delta = tonumber(delta) or 0
	sync_layout(number_var("Index", 0) + delta)
	update_view()
end

function AnimateNote(slot, delta)
	slot = tonumber(slot)
	delta = tonumber(delta) or 0
	if not slot or slot < 0 or slot > 7 then
		return
	end

	if delta > 0 and not has_note(slot) then
		SKIN:Bang("!SetVariable", "Nte.Open" .. slot, "0")
		SKIN:Bang("!SetVariable", "Nte.Anim" .. slot, "0")
		sync_layout()
		update_view()
		return
	end

	local anim = clamp(number_var("Nte.Anim" .. slot, 0) + delta, 0, 1)
	SKIN:Bang("!SetVariable", "Nte.Anim" .. slot, fmt(anim))
	if anim <= 0 then
		SKIN:Bang("!SetVariable", "Nte.Open" .. slot, "0")
	elseif anim >= 1 then
		SKIN:Bang("!SetVariable", "Nte.Open" .. slot, "1")
	end
	sync_layout()
	update_view()
end

function Swap(slot_a, slot_b)
	slot_a = tonumber(slot_a)
	slot_b = tonumber(slot_b)
	if not slot_a or not slot_b or slot_a < 0 or slot_b < 0 or slot_a > 7 or slot_b > 7 then
		return
	end
	if value(slot_a, "Hdn") == "1" or value(slot_b, "Hdn") == "1" then
		return
	end

	local a = {}
	local b = {}
	for _, field in ipairs(fields) do
		a[field] = value(slot_a, field)
		b[field] = value(slot_b, field)
	end

	for _, field in ipairs(fields) do
		write(slot_a, field, b[field])
		write(slot_b, field, a[field])
	end

	SKIN:Bang("!WriteKeyValue", "Variables", "PrvIndex", SKIN:GetVariable("Index", "0"), settings_path())
	SKIN:Bang("!Refresh")
end

function ToggleNote(slot)
	slot = tonumber(slot)
	if not slot or slot < 0 or slot > 7 then
		return
	end

	local name = "Nte.Open" .. slot
	local opening = number_var("Nte.Anim" .. slot, 0) <= 0
	if opening and not has_note(slot) then
		SKIN:Bang("!SetVariable", name, "0")
		SKIN:Bang("!SetVariable", "Nte.Anim" .. slot, "0")
		sync_layout()
		update_view()
		return
	end
	SKIN:Bang("!SetVariable", name, opening and "1" or "0")
	SKIN:Bang("!CommandMeasure", "Ms.NteAn" .. slot, opening and "Execute 1" or "Execute 2")
	update_view()
end

function OpenNote(slot)
	slot = tonumber(slot)
	if not slot or slot < 0 or slot > 7 then
		return
	end

	SKIN:Bang("!SetVariable", "Nte.Open" .. slot, "1")
	SKIN:Bang("!SetVariable", "Nte.Anim" .. slot, "1")
	sync_layout()
	update_view()
end

function EditNote(slot)
	slot = tonumber(slot)
	if not slot or slot < 0 or slot > 7 then
		return
	end

	OpenNote(slot)
	SKIN:Bang("!ShowMeter", "Mt.NteEdit" .. slot)
	SKIN:Bang("!CommandMeasure", "Ms.NteEdit" .. slot, "ExecuteBatch 1")
	SKIN:Bang("!Redraw")
end
