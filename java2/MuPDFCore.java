package com.docin.mupdf;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.PointF;
import android.graphics.RectF;
import android.text.TextUtils;
import android.util.Log;

import com.docin.HKSearch.HKSearch;
import com.docin.zlibrary.ui.android.R;

import java.util.ArrayList;

public class MuPDFCore {
	/* load our native library */
	static {
//		System.load(PathUtil.getInsidePdfLibPath());
		System.loadLibrary("mupdf");
	}

	/* Readable members */
	private int numPages = -1;
	private float pageWidth;
	private float pageHeight;
	private long globals;
	private byte fileBuffer[];
	private String file_format;
	private String documentId;
	private String documentSid;
	private byte[] StringBuf;
	private TextChar[] textRects;
	private HKSearch[] searchRects;
	/* The native functions */
	private native long openFile(String filename);

	private native long openBuffer();

	private native String fileFormatInternal();

	private native int countPagesInternal();

	private native void gotoPageInternal(int localActionPageNum);

	private native float getPageWidth();

	private native float getPageHeight();

	private native void drawPage(Bitmap bitmap, int pageW, int pageH, int patchX, int patchY,
			int patchW, int patchH);

	private native void updatePageInternal(Bitmap bitmap, int page, int pageW, int pageH,
			int patchX, int patchY, int patchW, int patchH);

	private native RectF[] searchPage(String text);

	private native TextChar[][][][] text();

	private native TextChar[][] hktext();

	private native TextChar[] hkselect(float x0,float y0,float x1,float y1,int number);

	private native HKSearch[] hksearch(int[]unicodes,int page);

	private native byte[] textAsHtml();

	private native void addMarkupAnnotationInternal(PointF[] quadPoints, int type);

	private native void addInkAnnotationInternal(PointF[][] arcs);

	private native void deleteAnnotationInternal(int annot_index);

	private native int passClickEventInternal(int page, float x, float y);

	private native void setFocusedWidgetChoiceSelectedInternal(String[] selected);

	private native String[] getFocusedWidgetChoiceSelected();

	private native String[] getFocusedWidgetChoiceOptions();

	private native int setFocusedWidgetTextInternal(String text);

	private native String getFocusedWidgetTextInternal();

	private native int getFocusedWidgetTypeInternal();

	private native LinkInfo[] getPageLinksInternal(int page);

	private native RectF[] getWidgetAreasInternal(int page);

	private native Annotation[] getAnnotationsInternal(int page);

	private native OutlineItem[] getOutlineInternal();

	private native boolean hasOutlineInternal();

	private native boolean needsPasswordInternal();

	private native boolean authenticatePasswordInternal(String password);

	private native MuPDFAlertInternal waitForAlertInternal();

	private native void replyToAlertInternal(MuPDFAlertInternal alert);

	private native void startAlertsInternal();

	private native void stopAlertsInternal();

	private native void destroying();

	private native boolean hasChangesInternal();

	private native void saveInternal();

	public native boolean javascriptSupported();

	public MuPDFCore(Context context, String filename) throws Exception {
		globals = openFile(filename);
		if (globals == 0) {
			throw new Exception(String.format(context.getString(R.string.cannot_open_file_Path),
					filename));
		}
		file_format = fileFormatInternal();
	}

	public MuPDFCore(Context context, byte buffer[]) throws Exception {
		fileBuffer = buffer;
		globals = openBuffer();
		if (globals == 0) {
			throw new Exception(context.getString(R.string.cannot_open_buffer));
		}
		file_format = fileFormatInternal();
	}

	public void setDocumentId(String documentId) {
		this.documentId = documentId;
	}

	public void setDocumentSid(String documentSid) {
		this.documentSid = documentSid;
	}

    public void setNumPages(int numPages) {
        this.numPages = numPages;
    }

	public int countPages() {
		if (numPages < 0)
			numPages = countPagesSynchronized();

		return numPages;
	}

	public String fileFormat() {
		return file_format;
	}

	private synchronized int countPagesSynchronized() {
		return countPagesInternal();
	}

	/* Shim function */
	private void gotoPage(int page) {
		if (page > numPages - 1)
			page = numPages - 1;
		else if (page < 0)
			page = 0;
		gotoPageInternal(page);
		this.pageWidth = getPageWidth();
		this.pageHeight = getPageHeight();
	}

	public synchronized PointF getPageSize(int page) {
		gotoPage(page);
		return new PointF(pageWidth, pageHeight);
	}

	public MuPDFAlert waitForAlert() {
		MuPDFAlertInternal alert = waitForAlertInternal();
		return alert != null ? alert.toAlert() : null;
	}

	public void replyToAlert(MuPDFAlert alert) {
		replyToAlertInternal(new MuPDFAlertInternal(alert));
	}

	public void stopAlerts() {
		stopAlertsInternal();
	}

	public void startAlerts() {
		startAlertsInternal();
	}

	public synchronized void drawPage(int page, Bitmap bitmap, int pageW, int pageH, int patchX,
			int patchY, int patchW, int patchH) {
		gotoPage(page);
		drawPage(bitmap, pageW, pageH, patchX, patchY, patchW, patchH);
	}

	public synchronized void onDestroy() {
		destroying();
		globals = 0;
	}

	private boolean memAlert = false;

	public synchronized Bitmap drawPage(int page, int pageW, int pageH, int patchX, int patchY,
			int patchW, int patchH) {
		gotoPage(page);
		Bitmap bm = null;
		try {
			bm = Bitmap.createBitmap(patchW, patchH, Config.ARGB_8888);
		} catch (java.lang.OutOfMemoryError e) {
			if (!memAlert) {
				memAlert = true;
				AlertDialog alertDialog = MuPDFActivity.getAlertBuilder().create();
				alertDialog.setMessage("Out of memory during draw");
				alertDialog.setButton(AlertDialog.BUTTON_NEUTRAL, "OK",
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int which) {
								dialog.dismiss();
								memAlert = false;
							}
						});
				alertDialog.show();
			}
		}
		if (bm != null) {
			drawPage(bm, pageW, pageH, patchX, patchY, patchW, patchH);
		}

		return bm;
	}

	public synchronized Bitmap updatePage(BitmapHolder h, int page, int pageW, int pageH,
			int patchX, int patchY, int patchW, int patchH) {
		Bitmap bm = null;
		Bitmap old_bm = h.getBm();

		if (old_bm == null)
			return null;

		bm = old_bm.copy(Bitmap.Config.ARGB_8888, false);
		old_bm = null;

		updatePageInternal(bm, page, pageW, pageH, patchX, patchY, patchW, patchH);
		return bm;
	}

	public synchronized PassClickResult passClickEvent(int page, float x, float y) {
		boolean changed = passClickEventInternal(page, x, y) != 0;

		switch (WidgetType.values()[getFocusedWidgetTypeInternal()]) {
		case TEXT:
			return new PassClickResultText(changed, getFocusedWidgetTextInternal());
		case LISTBOX:
		case COMBOBOX:
			return new PassClickResultChoice(changed, getFocusedWidgetChoiceOptions(),
					getFocusedWidgetChoiceSelected());
		default:
			return new PassClickResult(changed);
		}

	}

	public synchronized boolean setFocusedWidgetText(int page, String text) {
		boolean success;
		gotoPage(page);
		success = setFocusedWidgetTextInternal(text) != 0 ? true : false;

		return success;
	}

	public synchronized void setFocusedWidgetChoiceSelected(String[] selected) {
		setFocusedWidgetChoiceSelectedInternal(selected);
	}

	public synchronized LinkInfo[] getPageLinks(int page) {
		return getPageLinksInternal(page);
	}

	public synchronized RectF[] getWidgetAreas(int page) {
		return getWidgetAreasInternal(page);
	}

	public synchronized Annotation[] getAnnoations(int page) {
		return getAnnotationsInternal(page);
	}

	public synchronized RectF[] searchPage(int page, String text) {
		gotoPage(page);
		return searchPage(text);
	}

	public synchronized byte[] html(int page) {
		gotoPage(page);
		return textAsHtml();
	}

	public synchronized boolean isDocument() {
		return !TextUtils.isEmpty(documentId) && !TextUtils.isEmpty(documentSid);
	}

	public synchronized TextChar[] hkselect(RectF selectBox, int page) {
		int[]unicodes = {20896,32,32,32,31119,32};
		hksearch(unicodes,page);
		displaySearchTexts();
//		hkselect(0,0,Float.MAX_VALUE,300, page);
		hkselect(selectBox.left, selectBox.top, selectBox.right, selectBox.bottom, page);
		return this.textRects;
	}

	public synchronized TextChar[][] textLines(int page) {
		gotoPage(page);

		// The text of the page held in a hierarchy (blocks, lines, spans).
		// Currently we don't need to distinguish the blocks level or
		// the spans, and we need to collect the text into words.
		TextChar[][][][] chars = text();
		Log.d("testPdfOpen", "textLines: chars.length=" + chars.length);

		ArrayList<TextChar[]> lns = new ArrayList<>();
		for (TextChar[][][] bl : chars) {
			if (bl == null)
				continue;

			for (TextChar[][] ln : bl) {
				ArrayList<TextChar> chs = new ArrayList<>();

				for (TextChar[] wd : ln) {
					for (TextChar tc : wd) {
						if (!chs.contains(tc)) {
							chs.add(tc);
						}
					}
				}

				if (chs.size() > 0)
					lns.add(chs.toArray(new TextChar[chs.size()]));
			}
		}

		return lns.toArray(new TextChar[lns.size()][]);
	}

	public synchronized void addMarkupAnnotation(int page, PointF[] quadPoints, Annotation.Type type) {
		gotoPage(page);
		addMarkupAnnotationInternal(quadPoints, type.ordinal());
	}

	public synchronized void addInkAnnotation(int page, PointF[][] arcs) {
		gotoPage(page);
		addInkAnnotationInternal(arcs);
	}

	public synchronized void deleteAnnotation(int page, int annot_index) {
		gotoPage(page);
		deleteAnnotationInternal(annot_index);
	}

	public synchronized boolean hasOutline() {
		return hasOutlineInternal();
	}

	public synchronized OutlineItem[] getOutline() {
		return getOutlineInternal();
	}

	public synchronized boolean needsPassword() {
		return needsPasswordInternal();
	}

	public synchronized boolean authenticatePassword(String password) {
		return authenticatePasswordInternal(password);
	}

	public synchronized boolean hasChanges() {
		return hasChangesInternal();
	}

	public synchronized void save() {
		saveInternal();
	}

	public void setStringBuf(byte[] buffer) {
		this.StringBuf = buffer;
	}

	public void setTextRects(TextChar[] textRects)
	{
		this.textRects = textRects;
	}

	public void setSearchRects(HKSearch[] searchRects)
	{
		this.searchRects = searchRects;
	}

	public void displayUnicode()
	{
		Log.d("testPdfOpen", "StringBuf.length: " + StringBuf.length);
		int i;
		for (i=0;i<this.StringBuf.length;i=i+2)
		{
			int low = this.StringBuf[i]&0xff;
			int high = (this.StringBuf[i+1]&0xff)<<8;
			int unicode = low + high;
			Log.d("testPdfOpen", "unicode: " + unicode);
		}
	}

	public void displaySearchTexts()
	{
		Log.d("testPdfOpen", "StringBuf.length: " + this.searchRects.length);
		int i = 0;
		for (i=0;i<this.searchRects.length;i++)
		{
			Log.d("testPdfOpen", "search: ");
			HKSearch s = this.searchRects[i];
			TextChar[] rects = s.textRects;
			byte[] StringBuf =s.StringBuf;
			for (i=0;i<rects.length;i++)
			{
				TextChar r = rects[i];
				Log.d("testPdfOpen", "rect: " + r.left + r.top + r.right + r.bottom);
			}
			for (i=0;i<StringBuf.length;i=i+2)
			{
				int low = StringBuf[i]&0xff;
				int high = (StringBuf[i+1]&0xff)<<8;
				int unicode = low + high;
				Log.d("testPdfOpen", "unicode: " + unicode);
			}
		}
	}
}
