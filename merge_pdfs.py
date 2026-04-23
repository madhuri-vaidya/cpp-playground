import fitz  # PyMuPDF
import os
from tqdm import tqdm

# Configuration
SOURCE_FOLDER = "./pdf_sources/"
OUTPUT_NAME = "Computer_Architecture"
# 195MB buffer to ensure we never hit the hard 200MB limit
MAX_SIZE_BYTES = 195 * 1024 * 1024 

def merge_pdfs():
    # Get all PDFs and sort them so your notes stay in order
    pdf_files = sorted([f for f in os.listdir(SOURCE_FOLDER) if f.endswith('.pdf')])
    
    if not pdf_files:
        print("No PDF files found in the source folder!")
        return

    doc = fitz.open()
    current_batch_size = 0
    batch_num = 1

    print(f"Starting merge of {len(pdf_files)} files...")
    
    for file_name in tqdm(pdf_files, desc="Processing Files"):
        path = os.path.join(SOURCE_FOLDER, file_name)
        file_size = os.path.getsize(path)

        # Check if adding this file would exceed the 200MB limit
        if (current_batch_size + file_size) > MAX_SIZE_BYTES and len(doc) > 0:
            output_name = f"{OUTPUT_NAME}_{batch_num}.pdf"
            print(f"\nFinalizing {output_name} (this may take a moment with garbage=4)...")
            
            # The 'Gold Standard' Save Settings
            doc.save(output_name, 
                     garbage=4, 
                     deflate=True, 
                     use_objstms=True)
            
            doc.close()
            doc = fitz.open()
            current_batch_size = 0
            batch_num += 1

        # Add the PDF to the current batch
        try:
            with fitz.open(path) as m_file:
                doc.insert_pdf(m_file)
                current_batch_size += file_size

        except Exception as e:
            print(f"Error reading {file_name}: {e}")

    # Save the final batch
    if len(doc) > 0:
        final_name = f"{OUTPUT_NAME}_{batch_num}.pdf"
        doc.save(final_name, garbage=4, deflate=True, use_objstms=True)
        doc.close()
        print(f"\n✅ All batches complete! Final file: {final_name}")

if __name__ == "__main__":
    merge_pdfs()
