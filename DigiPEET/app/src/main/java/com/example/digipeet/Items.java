package com.example.digipeet;

public class Items {
    String Product, Quantity, Code;

    private Items(){}

    private Items(String product, String quantity, String code) {
        this.Product = product;
        this.Quantity = quantity;
        this.Code = code;
    }

    public String getProduct() {
        return Product;
    }

    public void setProduct(String product) {
        Product = product;
    }

    public String getQuantity() {
        return Quantity;
    }

    public void setQuantity(String quantity) {
        Quantity = quantity;
    }

    public String getCode() {
        return Code;
    }

    public void setCode(String code) {
        Code = code;
    }
}
