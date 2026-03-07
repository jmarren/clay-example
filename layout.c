// #include "clay.h"
#include "clay/clay.h"

Clay_RenderCommandArray create_layout(void) {
	Clay_BeginLayout();
	
	Clay_Sizing layoutExpand = {
		.width = CLAY_SIZING_GROW(0),
		.height = CLAY_SIZING_GROW(0),
	};

	Clay_Color contentBackgroundColor = { 90, 90, 90, 255 };

	CLAY(CLAY_ID("OuterContainer"), {
		.backgroundColor = { 43, 41, 51, 255 },
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = layoutExpand,
			.padding = CLAY_PADDING_ALL(16),
			.childGap = 16
		}

			});

    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    // for (int32_t i = 0; i < renderCommands.length; i++) {
    //     Clay_RenderCommandArray_Get(&renderCommands, i)->boundingBox.y += data->yOffset;
    // }
    return renderCommands;



}


// Clay_RenderCommandArray ClayVideoDemo_CreateLayout(ClayVideoDemo_Data *data) {
//     data->frameArena.offset = 0;
//
//     Clay_BeginLayout();
//
//     Clay_Sizing layoutExpand = {
//         .width = CLAY_SIZING_GROW(0),
//         .height = CLAY_SIZING_GROW(0)
//     };
//
//     Clay_Color contentBackgroundColor = { 90, 90, 90, 255 };
//
//     // Build UI here
//     CLAY(CLAY_ID("OuterContainer"), {
//         .backgroundColor = {43, 41, 51, 255 },
//         .layout = {
//             .layoutDirection = CLAY_TOP_TO_BOTTOM,
//             .sizing = layoutExpand,
//             .padding = CLAY_PADDING_ALL(16),
//             .childGap = 16
//         }
//     }) {
//         // Child elements go inside braces
//         CLAY(CLAY_ID("HeaderBar"), {
//             .layout = {
//                 .sizing = {
//                     .height = CLAY_SIZING_FIXED(60),
//                     .width = CLAY_SIZING_GROW(0)
//                 },
//                 .padding = { 16, 16, 0, 0 },
//                 .childGap = 16,
//                 .childAlignment = {
//                     .y = CLAY_ALIGN_Y_CENTER
//                 }
//             },
//             .backgroundColor = contentBackgroundColor,
//             .cornerRadius = CLAY_CORNER_RADIUS(8)
//         }) {
//             // Header buttons go here
//             CLAY(CLAY_ID("FileButton"), {
//                 .layout = { .padding = { 16, 16, 8, 8 }},
//                 .backgroundColor = {140, 140, 140, 255 },
//                 .cornerRadius = CLAY_CORNER_RADIUS(5)
//             }) {
//                 CLAY_TEXT(CLAY_STRING("File"), CLAY_TEXT_CONFIG({
//                     .fontId = FONT_ID_BODY_16,
//                     .fontSize = 16,
//                     .textColor = { 255, 255, 255, 255 }
//                 }));
//
//                 bool fileMenuVisible =
//                     Clay_PointerOver(Clay_GetElementId(CLAY_STRING("FileButton")))
//                     ||
//                     Clay_PointerOver(Clay_GetElementId(CLAY_STRING("FileMenu")));
//
//                 if (fileMenuVisible) { // Below has been changed slightly to fix the small bug where the menu would dismiss when mousing over the top gap
//                     CLAY(CLAY_ID("FileMenu"), {
//                         .floating = {
//                             .attachTo = CLAY_ATTACH_TO_PARENT,
//                             .attachPoints = {
//                                 .parent = CLAY_ATTACH_POINT_LEFT_BOTTOM
//                             },
//                         },
//                         .layout = {
//                             .padding = {0, 0, 8, 8 }
//                         }
//                     }) {
//                         CLAY_AUTO_ID({
//                             .layout = {
//                                 .layoutDirection = CLAY_TOP_TO_BOTTOM,
//                                 .sizing = {
//                                         .width = CLAY_SIZING_FIXED(200)
//                                 },
//                             },
//                             .backgroundColor = {40, 40, 40, 255 },
//                             .cornerRadius = CLAY_CORNER_RADIUS(8)
//                         }) {
//                             // Render dropdown items here
//                             RenderDropdownMenuItem(CLAY_STRING("New"));
//                             RenderDropdownMenuItem(CLAY_STRING("Open"));
//                             RenderDropdownMenuItem(CLAY_STRING("Close"));
//                         }
//                     }
//                 }
//             }
//             RenderHeaderButton(CLAY_STRING("Edit"));
//             CLAY_AUTO_ID({ .layout = { .sizing = { CLAY_SIZING_GROW(0) }}}) {}
//             RenderHeaderButton(CLAY_STRING("Upload"));
//             RenderHeaderButton(CLAY_STRING("Media"));
//             RenderHeaderButton(CLAY_STRING("Support"));
//         }
//
//         CLAY(CLAY_ID("LowerContent"), {
//             .layout = { .sizing = layoutExpand, .childGap = 16 }
//         }) {
//             CLAY(CLAY_ID("Sidebar"), {
//                 .backgroundColor = contentBackgroundColor,
//                 .layout = {
//                     .layoutDirection = CLAY_TOP_TO_BOTTOM,
//                     .padding = CLAY_PADDING_ALL(16),
//                     .childGap = 8,
//                     .sizing = {
//                         .width = CLAY_SIZING_FIXED(250),
//                         .height = CLAY_SIZING_GROW(0)
//                     }
//                 }
//             }) {
//                 for (int i = 0; i < documents.length; i++) {
//                     Document document = documents.documents[i];
//                     Clay_LayoutConfig sidebarButtonLayout = {
//                         .sizing = { .width = CLAY_SIZING_GROW(0) },
//                         .padding = CLAY_PADDING_ALL(16)
//                     };
//
//                     if (i == data->selectedDocumentIndex) {
//                         CLAY_AUTO_ID({
//                             .layout = sidebarButtonLayout,
//                             .backgroundColor = {120, 120, 120, 255 },
//                             .cornerRadius = CLAY_CORNER_RADIUS(8)
//                         }) {
//                             CLAY_TEXT(document.title, CLAY_TEXT_CONFIG({
//                                 .fontId = FONT_ID_BODY_16,
//                                 .fontSize = 20,
//                                 .textColor = { 255, 255, 255, 255 }
//                             }));
//                         }
//                     } else {
//                         SidebarClickData *clickData = (SidebarClickData *)(data->frameArena.memory + data->frameArena.offset);
//                         *clickData = (SidebarClickData) { .requestedDocumentIndex = i, .selectedDocumentIndex = &data->selectedDocumentIndex };
//                         data->frameArena.offset += sizeof(SidebarClickData);
//                         CLAY_AUTO_ID({ .layout = sidebarButtonLayout, .backgroundColor = (Clay_Color) { 120, 120, 120, (float)(Clay_Hovered() ? 120 : 0) }, .cornerRadius = CLAY_CORNER_RADIUS(8) }) {
//                             Clay_OnHover(HandleSidebarInteraction, clickData);
//                             CLAY_TEXT(document.title, CLAY_TEXT_CONFIG({
//                                 .fontId = FONT_ID_BODY_16,
//                                 .fontSize = 20,
//                                 .textColor = { 255, 255, 255, 255 }
//                             }));
//                         }
//                     }
//                 }
//             }
//
//             CLAY(CLAY_ID("MainContent"), {
//                 .backgroundColor = contentBackgroundColor,
//                 .clip = { .vertical = true, .childOffset = Clay_GetScrollOffset() },
//                 .layout = {
//                     .layoutDirection = CLAY_TOP_TO_BOTTOM,
//                     .childGap = 16,
//                     .padding = CLAY_PADDING_ALL(16),
//                     .sizing = layoutExpand
//                 }
//             }) {
//                 Document selectedDocument = documents.documents[data->selectedDocumentIndex];
//                 CLAY_TEXT(selectedDocument.title, CLAY_TEXT_CONFIG({
//                     .fontId = FONT_ID_BODY_16,
//                     .fontSize = 24,
//                     .textColor = COLOR_WHITE
//                 }));
//                 CLAY_TEXT(selectedDocument.contents, CLAY_TEXT_CONFIG({
//                     .fontId = FONT_ID_BODY_16,
//                     .fontSize = 24,
//                     .textColor = COLOR_WHITE
//                 }));
//             }
//         }
//     }
//
//     Clay_RenderCommandArray renderCommands = Clay_EndLayout();
//     for (int32_t i = 0; i < renderCommands.length; i++) {
//         Clay_RenderCommandArray_Get(&renderCommands, i)->boundingBox.y += data->yOffset;
//     }
//     return renderCommands;
// }
